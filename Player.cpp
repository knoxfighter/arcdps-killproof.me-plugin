#include "Player.h"

#include <set>
#include <cpr/cpr.h>
#include <cpr/util.h>

#include "global.h"
#include "json.hpp"
#include "KillproofUI.h"
#include "extension/UpdateCheckerBase.h"

void Player::loadKillproofs() {
	using namespace std::chrono_literals;

	// make sure this is not run twice
	// So we skip, if the players data is unavailable, already loading or successfully loaded
	LoadingStatus loadingStatus = status.load();
	if (loadingStatus == LoadingStatus::LoadingById || loadingStatus == LoadingStatus::LoadingByChar ||
		loadingStatus == LoadingStatus::NoDataAvailable || loadingStatus == LoadingStatus::Loaded)
		return;
	// not run if Loading cannot be set or loading status was previously something different
	if (!status.compare_exchange_strong(loadingStatus, LoadingStatus::LoadingById))
		return;

	// download it in a new thread (fire and forget)
	const auto call = [this](const auto& self, const std::string& link) -> void {
		std::string version = UpdateCheckerBase::GetVersionAsString(self_dll);
		std::string userAgent = "arcdps-killproof.me-plugin/";
		userAgent.append(version);
		cpr::Response response = cpr::Get(cpr::Url{link}, cpr::Header{{"User-Agent", userAgent }}, cpr::Ssl(cpr::ssl::TLSv1_2{}));

		if (response.status_code == 200) {
			auto json = nlohmann::json::parse(response.text);

			// get kpid and accountname
			killproofId = json.at("kpid").get<std::string>();
			std::string accountname = json.at("account_name").get<std::string>();

			// replace the key in the global map, when kpid or charname was used to create this player
			if (username == killproofId || username != accountname) {
				// lock the maps
				std::scoped_lock<std::mutex, std::mutex, std::mutex> lock(trackedPlayersMutex, instancePlayersMutex, cachedPlayersMutex);

				// replace the key of the cache
				auto node = cachedPlayers.extract(username);
				node.key() = accountname;
				const auto inserRes = cachedPlayers.insert(std::move(node));

				// When insertion of changed node fails, the key already exists and `this` gets destructed.
				// Therefore `this` is invalid and going on further results in an UseAfterFree !
				if (!inserRes.inserted) {
					// last action to do: remove the wrong username from the list of tracked players
					removePlayer(username);
					return;
				}

				// replace the player in tracked players
				std::ranges::replace(trackedPlayers, username, accountname);
				std::ranges::replace(instancePlayers, username, accountname);

				// set the username as charactername
				if (username != killproofId && username != accountname) {
					characterName = username;
				}
			}

			// set username AFTER the check, if it the same as the kpid
			username = accountname;

			loadKPs(json, killproofs, coffers);

			if (json.contains("linked_totals")) {
				auto linked_totals = json.at("linked_totals");
				Killproofs& killproofs = linkedTotalKillproofs.emplace();
				Coffers& coffers = linkedTotalCoffers.emplace();
				loadKPs(linked_totals, killproofs, coffers);
			}

			if (json.contains("linked")) {
				for (auto linked : json.at("linked")) {
					std::string accountName = linked.at("account_name").get<std::string>();
					const auto& playerEmplace = cachedPlayers.try_emplace(accountName, accountName, AddedBy::Miscellaneous);
					if (playerEmplace.second) {
						Player& player = playerEmplace.first->second;
						player.killproofId = linked.at("kpid").get<std::string>();
						loadKPs(linked, player.killproofs, player.coffers);
					}

					linkedAccounts.emplace_back(accountName);
				}
			}

			this->status = LoadingStatus::Loaded;
		}
		// silently set, when user not found
		else if (response.status_code == 404) {
			this->killproofs.setAllKillproofFieldsToBlocked();
			this->killproofs.setAllTokensFieldsToBlocked();
			this->linkedTotalKillproofs.reset();

			// try again as charactername (only when manually added)
			if (status == LoadingStatus::LoadingById && addedBy == AddedBy::Manually) {
				std::string new_link = "https://killproof.me/api/character/";
				new_link.append(cpr::util::urlEncode(username));
				new_link.append("/kp?lang=en");
				status = LoadingStatus::LoadingByChar;
				self(self, new_link);
			} else {
				status = LoadingStatus::NoDataAvailable;
			}
		}
		// on any other error, print verbose output into the arcdps.log file
		else {
			this->status = LoadingStatus::KpMeError;

			std::string cs = "URL: ";
			cs.append(response.url.str());
			cs.append(" -- Status: ");
			cs.append(std::to_string(response.status_code));
			cs.append(" -- Response: ");
			cs.append(response.text);
			cs.append(" -- ErrorMessage: ");
			cs.append(response.error.message);
			cs.append(" -- Reason: ");
			cs.append(response.reason);
			cs.append(" -- StatusLine: ");
			cs.append(response.status_line);
			cs.append("\n");
			arc_log_file(cs.c_str());

			this->errorMessage = cs;

			// start 1 minute timeout until reloading
			// we can just pause this detached thread :)
			std::this_thread::sleep_for(1min);
			this->loadKillproofs();
		}

		// say UI to reload sorting
		killproofUi.needSort = true;
	};

	// create the link for getting by accountname/kpid
	std::string link = "https://killproof.me/api/kp/";
	link.append(cpr::util::urlEncode(username));
	link.append("?lang=en");

	// call the created lambda in a new thread
	std::thread cprCall(call, call, link);

	// we want to run async completely, so just detach
	cprCall.detach();
}

amountVal Player::getKpOverall(const Killproof& kp) const {
	amountVal killproofAmount = killproofs.getAmount(kp);
	amountVal cofferAmount = coffers.getAmount(kp);
	amountVal totalAmount = killproofAmount;
	if (kp == Killproof::li || kp == Killproof::ld || kp == Killproof::liLd) {
		totalAmount += cofferAmount;
	}
	else {
		totalAmount += cofferAmount * settings.getCofferValue();
	}
	return totalAmount;
}

amountVal Player::getKillproofsTotal(const Killproof& kp) const {
	if (linkedTotalKillproofs) {
		return linkedTotalKillproofs->getAmount(kp);
	}
	return 0;
}

amountVal Player::getCoffersTotal(const Killproof& kp) const {
	if (linkedTotalCoffers) {
		return linkedTotalCoffers->getAmount(kp);
	}
	return 0;
}

amountVal Player::getKpOverallTotal(const Killproof& kp) const {
	amountVal killproofAmount = getKillproofsTotal(kp);
	amountVal cofferAmount = getCoffersTotal(kp);
	amountVal totalAmount = killproofAmount;
	if (kp == Killproof::li || kp == Killproof::ld || kp == Killproof::liLd) {
		totalAmount += cofferAmount;
	}
	else {
		totalAmount += cofferAmount * settings.getCofferValue();
	}
	return totalAmount;
}

void Player::loadKPs(nlohmann::json& json, Killproofs& killproofStorage, Coffers& cofferStorage) {
	auto tokens = json.at("tokens");
	// when field is null, data is not available
	if (tokens.is_null()) {
		// set all tokens fields to -1
		killproofStorage.setAllTokensFieldsToBlocked();
	}
	// else it is an array (can be empty)
	else if (tokens.is_array()) {
		for (auto token : tokens) {
			auto id = token.at("id");
			if (id.is_string()) {
				killproofStorage.setAmountFromId(id.get<std::string>(), token.at("amount"));
			} else if (id.is_number_integer()) {
				killproofStorage.setAmountFromId(id.get<int>(), token.at("amount"));
			}
		}
	}

	auto killproofs = json.at("killproofs");
	// when field is null, data is not available
	if (killproofs.is_null()) {
		// set all killproof fields to -1
		killproofStorage.setAllKillproofFieldsToBlocked();
	}
	// else it is an array (can be empty)
	else if (killproofs.is_array()) {
		// track all used killproof IDs
		std::set<int> unUsedKPs = { 77302, 81743, 88485, 94020, 93781 };

		// iterate over all available killproofs
		for (auto killproof : killproofs) {
			int kpId = killproof.at("id").get<int>();
			unUsedKPs.erase(kpId);
			killproofStorage.setAmountFromId(kpId, killproof.at("amount"));
		}

		// set rest KPs to blocked
		for (int unUsedKP : unUsedKPs) {
			killproofStorage.setBlockedFromId(unUsedKP);
		}
	}

	auto coffers = json.at("coffers");
	if (coffers.is_null()) {
		cofferStorage.setAllTokensFieldsToBlocked();
	} else if (coffers.is_array()) {
		for (auto coffer : coffers) {
			int cofferId = coffer.at("id").get<int>();

			cofferStorage.setAmount(cofferId, coffer.at("amount"));
		}
	}
}
