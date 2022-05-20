#include "Player.h"

#include "global.h"
#include "KillproofUI.h"
#include "Settings.h"

#include "extension/arcdps_structs.h"

#include <set>

#include <cpr/cpr.h>
#include <cpr/util.h>

#include <nlohmann/json.hpp>

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
		std::string version = UpdateChecker::instance().GetVersionAsString(
			*GlobalObjects::UPDATE_STATE->CurrentVersion);
		std::string userAgent = "arcdps-killproof.me-plugin/";
		userAgent.append(version);
		cpr::Response response = cpr::Get(cpr::Url{link}, cpr::Header{{"User-Agent", userAgent}},
		                                  cpr::Ssl(cpr::ssl::TLSv1_2{}));

		if (response.status_code == 200) {
			auto json = nlohmann::json::parse(response.text);

			// get accountname
			std::string accountname = json.at("account_name").get<std::string>();

			// replace the key in the global map, when kpid or charname was used to create this player
			if (username != accountname) {
				// lock the maps
				std::scoped_lock<std::mutex, std::mutex, std::mutex> lock(
					trackedPlayersMutex, instancePlayersMutex, cachedPlayersMutex);

				// replace the key of the cache
				auto node = cachedPlayers.extract(username);
				node.key() = accountname;
				const auto insertRes = cachedPlayers.insert(std::move(node));

				// When insertion of changed node fails, the key already exists and `this` gets destructed.
				// Therefore `this` is invalid and going on further results in an UseAfterFree !
				if (!insertRes.inserted) {
					// last action to do: remove the wrong username from the list of tracked players
					removePlayer(username, AddedBy::Miscellaneous);
					// add the new accountname to display, if it is currently not shown
					addPlayerTracking(accountname);
					// add charactername to correct user
					Player& actualPlayer = cachedPlayers.at(accountname);
					if (status == LoadingStatus::LoadingByChar) {
						actualPlayer.characterName = username;
					}
					if (actualPlayer.status == LoadingStatus::NoDataAvailable || actualPlayer.status == LoadingStatus::LoadedByLinked) {
						actualPlayer.LoadAll(json);
					}
					return;
				}

				// replace the player in tracked players
				std::ranges::replace(trackedPlayers, username, accountname);
				std::ranges::replace(instancePlayers, username, accountname);

				// set the username as charactername
				if (this->status == LoadingStatus::LoadingByChar) {
					characterName = username;
				}
			}

			// set username AFTER the check, if it is the same as the kpid
			username = accountname;

			LoadAll(json);
		}
		// silently set, when user not found
		else if (response.status_code == 404) {
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
			ARC_LOG_FILE(cs.c_str());

			this->errorMessage = cs;

			// start 1 minute timeout until reloading
			// we can just pause this detached thread :)
			std::this_thread::sleep_for(1min);
			this->loadKillproofs();
		}

		// say UI to reload sorting
		KillproofUI::instance().GetTable()->RequestSort();
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

std::optional<amountVal> Player::getKpOverall(const Killproof& kp) const {
	const auto& killproofAmount = killproofs.GetAmount(kp);
	const auto& cofferAmount = coffers.GetAmount(kp);

	if (!killproofAmount && !cofferAmount) return std::nullopt;

	amountVal totalAmount = killproofAmount ? killproofAmount.value() : 0;

	if (cofferAmount) {
		if (kp == Killproof::li || kp == Killproof::ld || kp == Killproof::liLd) {
			totalAmount += cofferAmount.value();
		} else {
			totalAmount += cofferAmount.value() * Settings::instance().settings.cofferValue;
		}
	}
	return totalAmount;
}

std::optional<amountVal> Player::getKillproofsTotal(const Killproof& kp) const {
	return linkedTotalKillproofs ? linkedTotalKillproofs->GetAmount(kp) : std::nullopt;
}

std::optional<amountVal> Player::getCoffersTotal(const Killproof& kp) const {
	return linkedTotalCoffers ? linkedTotalCoffers->GetAmount(kp) : std::nullopt;
}

std::optional<amountVal> Player::getKpOverallTotal(const Killproof& kp) const {
	const auto& killproofAmount = getKillproofsTotal(kp);
	const auto& cofferAmount = getCoffersTotal(kp);

	if (!killproofAmount && !cofferAmount) return std::nullopt;

	amountVal totalAmount = killproofAmount ? killproofAmount.value() : 0;

	if (cofferAmount) {
		if (kp == Killproof::li || kp == Killproof::ld || kp == Killproof::liLd) {
			totalAmount += cofferAmount.value();
		} else {
			totalAmount += cofferAmount.value() * Settings::instance().settings.cofferValue;
		}
	}
	return totalAmount;
}

void Player::LoadAll(const nlohmann::json& json) {
	// save kpid
	killproofId = json.at("kpid").get<std::string>();

	loadKPs(json, killproofs, coffers);

	if (json.contains("linked_totals")) {
		const auto linked_totals = json.at("linked_totals");
		Killproofs& killproofs = linkedTotalKillproofs.emplace();
		Killproofs& coffers = linkedTotalCoffers.emplace();
		loadKPs(linked_totals, killproofs, coffers);
	}

	if (json.contains("linked")) {
		for (auto linked : json.at("linked")) {
			std::string accountName = linked.at("account_name").get<std::string>();
			const auto& playerEmplace = cachedPlayers.try_emplace(accountName, accountName, AddedBy::Miscellaneous);
			if (playerEmplace.second) {
				Player& player = playerEmplace.first->second;
				player.killproofId = linked.at("kpid").get<std::string>();
				player.status = LoadingStatus::LoadedByLinked;
				loadKPs(linked, player.killproofs, player.coffers);
			}

			linkedAccounts.emplace_back(accountName);
		}
	}

	this->status = LoadingStatus::Loaded;
}

void Player::loadKPs(const nlohmann::json& json, Killproofs& killproofStorage, Killproofs& cofferStorage) {
	const auto& tokens = json.at("tokens");
	// when field is null, data is not available
	// else it is an array (can be empty)
	if (tokens.is_array()) {
		for (const auto& token : tokens) {
			auto id = token.at("id");
			if (id.is_string()) {
				killproofStorage.SetAmount(id.get<std::string>(), token.at("amount"));
			} else if (id.is_number_integer()) {
				killproofStorage.SetAmount(id.get<int>(), token.at("amount"));
			}
		}
	}

	const auto& killproofs = json.at("killproofs");
	// when field is null, data is not available
	// else it is an array (can be empty)
	if (killproofs.is_array()) {
		// iterate over all available killproofs
		for (const auto& killproof : killproofs) {
			int kpId = killproof.at("id").get<int>();
			killproofStorage.SetAmount(kpId, killproof.at("amount"));
		}
	}

	const auto& coffers = json.at("coffers");
	// when field is null, data is not available
	// else it is an array (can be empty)
	if (coffers.is_array()) {
		for (const auto& coffer : coffers) {
			int cofferId = coffer.at("id").get<int>();

			cofferStorage.SetAmount<true>(cofferId, coffer.at("amount"));
		}
	}

	if (json.contains("original_uce")) {
		const auto& originalUce = json.at("original_uce");
		if (originalUce.is_object()) {
			amountVal uce = originalUce.at("amount").get<amountVal>();
			if (uce > killproofStorage.GetAmount(Killproof::uce)) {
				killproofStorage.SetAmount(Killproof::uce, uce);
			}
		}
	}
}
