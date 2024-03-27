#include "Player.h"

#include "global.h"
#include "KillproofUI.h"
#include "Settings.h"

#include "ArcdpsExtension/arcdps_structs.h"

#include <set>
#include <ArcdpsExtension/SimpleNetworkStack.h>

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

	auto& networkStack = SimpleNetworkStack::instance();

	// create the link for getting by accountname/kpid
	std::string link = "https://killproof.me/api/kp/";
	link.append(networkStack.UrlEncode(username));
	link.append("?lang=en");

	networkStack.QueueGet(link, [username = username, url = link](const SimpleNetworkStack::Result& pResult) {
		websiteCallback(username, pResult, url);
	});
}

std::optional<amountVal> Player::getKpOverall(const Killproof& kp) const {
	const auto& killproofAmount = killproofs.GetAmount(kp);
	const auto& cofferAmount = coffers.GetAmount(kp);

	if (!killproofAmount && !cofferAmount) return std::nullopt;

	amountVal totalAmount = killproofAmount ? killproofAmount.value() : 0;

	if (cofferAmount) {
		if (kp == Killproof::liLd) {
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
		if (kp == Killproof::liLd) {
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

void Player::websiteCallback(const std::string& pUsername, const SimpleNetworkStack::Result& pResult, const std::string& pUrl) {
	using namespace std::chrono_literals;
	if (!pResult.has_value()) {
		// error message - unknown error
		const auto& error = pResult.error();

		std::lock_guard guard(cachedPlayersMutex);
		const auto& playerIt = cachedPlayers.find(pUsername);
		if (playerIt != cachedPlayers.end()) {
			auto& player = playerIt->second;
			player.status = LoadingStatus::KpMeError;

			std::string cs = "URL: ";
			cs.append(pUrl);
			cs.append(" -- Error: ");
			cs.append(std::format("{}", error.Type));
			cs.append(" -- ErrorStr: ");
			cs.append(error.Message);
			cs.append("\n");
			ARC_LOG_FILE(cs.c_str());

			player.errorMessage = cs;

			// start 1 minute timeout until reloading
			// we can just pause this detached thread :)
			std::this_thread::sleep_for(1min);
			player.loadKillproofs();
		}

		return;
	}

	if (pResult->Code == 200) {
		auto json = nlohmann::json::parse(pResult->Message);

		// get accountname
		std::string accountname = json.at("account_name").get<std::string>();

		// replace the key in the global map, when kpid or charname was used to create this player
		if (pUsername != accountname) {
			// lock the maps
			std::scoped_lock<std::mutex, std::mutex, std::mutex> lock(
				trackedPlayersMutex, instancePlayersMutex, cachedPlayersMutex);

			// replace the key of the cache
			// extracting invalidates the iterator!
			auto node = cachedPlayers.extract(pUsername);
			node.key() = accountname;
			const auto insertRes = cachedPlayers.insert(std::move(node));

			// When insertion of changed node fails, the key already exists and `this` gets destructed.
			// Therefore `this` is invalid and going on further results in an UseAfterFree !
			if (!insertRes.inserted) {
				// last action to do: remove the wrong username from the list of tracked players
				removePlayer(pUsername, AddedBy::Miscellaneous);
				// add the new accountname to display, if it is currently not shown
				addPlayerTracking(accountname);
				// add charactername to correct user
				Player& actualPlayer = cachedPlayers.at(accountname);
				if (insertRes.node.mapped().status == LoadingStatus::LoadingByChar) {
					actualPlayer.characterName = pUsername;
				}
				if (actualPlayer.status == LoadingStatus::NoDataAvailable || actualPlayer.status == LoadingStatus::LoadedByLinked) {
					actualPlayer.LoadAll(json);
				}
				return;
			}

			// replace the player in tracked players
			std::ranges::replace(trackedPlayers, pUsername, accountname);
			std::ranges::replace(instancePlayers, pUsername, accountname);

			// set the username as charactername
			if (insertRes.position->second.status == LoadingStatus::LoadingByChar) {
				insertRes.position->second.characterName = pUsername;
			}
		}

		// access to player in cache, lock it
		std::lock_guard guard(cachedPlayersMutex);

		// get player from list
		auto& player = cachedPlayers.at(accountname);

		// set username AFTER the check, in the case it is the same as the kpid
		player.username = accountname;

		player.LoadAll(json);
	}
	// silently set, when user not found
	else if (pResult->Code == 404) {
		std::lock_guard guard(cachedPlayersMutex);
		const auto& playerIt = cachedPlayers.find(pUsername);
		if (playerIt != cachedPlayers.end()) {
			auto& player = playerIt->second;

			// try again as charactername (only when manually added)
			if (player.status == LoadingStatus::LoadingById && player.addedBy == AddedBy::Manually) {
				auto& networkStack = SimpleNetworkStack::instance();
				std::string new_link = "https://killproof.me/api/character/";
				new_link.append(networkStack.UrlEncode(pUsername));
				new_link.append("/kp?lang=en");
				player.status = LoadingStatus::LoadingByChar;

				networkStack.QueueGet(new_link, [pUsername, url = new_link](const SimpleNetworkStack::Result& pResult) {
					websiteCallback(pUsername, pResult, url);
				});
			} else {
				player.status = LoadingStatus::NoDataAvailable;
			}
		}
	}
	// on any other error, print verbose output into the arcdps.log file
	else {
		std::lock_guard guard(cachedPlayersMutex);
		const auto& playerIt = cachedPlayers.find(pUsername);
		if (playerIt != cachedPlayers.end()) {
			auto& player = playerIt->second;
			player.status = LoadingStatus::KpMeError;

			std::string cs = "URL: ";
			cs.append(pUrl);
			cs.append(" -- Status-Code: ");
			cs.append(std::to_string(pResult->Code));
			cs.append(" -- Response: ");
			cs.append(pResult->Message);
			cs.append("\n");
			ARC_LOG_FILE(cs.c_str());

			player.errorMessage = cs;

			// start 1 minute timeout until reloading
			std::thread t([pUsername] {
				std::this_thread::sleep_for(1min);

				std::lock_guard guard(cachedPlayersMutex);
				const auto& playerIt = cachedPlayers.find(pUsername);
				if (playerIt != cachedPlayers.end()) {
					playerIt->second.loadKillproofs();
				}
			});
			t.detach();
		}
	}

	// say UI to reload sorting
	KillproofUI::instance().GetTable()->RequestSort();
}
