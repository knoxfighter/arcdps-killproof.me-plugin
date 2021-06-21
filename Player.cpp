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
		char* version = UpdateCheckerBase::GetVersionAsString(self_dll);
		std::string userAgent = "arcdps-killproof.me-plugin/";
		userAgent.append(version);
		cpr::Response response = cpr::Get(cpr::Url{link}, cpr::Header{{"User-Agent", userAgent }});

		if (response.status_code == 200) {
			auto json = nlohmann::json::parse(response.text);

			// get kpid and accountname
			killproofId = json.at("kpid").get<std::string>();
			std::string accountname = json.at("account_name").get<std::string>();

			// replace the key in the global map, when kpid or charname was used to create this player
			if (username == killproofId || username != accountname) {
				// lock the maps
				std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);

				// replace the key of the cache
				auto node = cachedPlayers.extract(username);
				node.key() = accountname;
				const auto inserRes = cachedPlayers.insert(std::move(node));

				// replace the player in tracked players
				std::replace(trackedPlayers.begin(), trackedPlayers.end(), username, accountname);
				
				// When insertion of changed node fails, the key already exists and `this` gets destructed.
				// Therefore `this` is invalid and going on further results in an UseAfterFree !
				if (!inserRes.inserted) {
					// last action to do: remove the wrong player from the tracked players list
					trackedPlayers.erase(std::remove(trackedPlayers.begin(), trackedPlayers.end(), username), trackedPlayers.end());
					return;
				}

				// set the username as charactername
				if (username != killproofId && username != accountname) {
					characterName = username;
				}
			}

			// set username AFTER the check, if it the same as the kpid
			username = accountname;

			loadKPs(json, killproofs);

			if (json.contains("linked_totals")) {
				auto linked_totals = json.at("linked_totals");
				Killproofs& killproofs = linkedTotalKillproofs.emplace();
				loadKPs(linked_totals, killproofs);
			}

			if (json.contains("linked")) {
				for (auto linked : json.at("linked")) {
					std::string accountName = linked.at("account_name").get<std::string>();
					const auto& playerEmplace = cachedPlayers.try_emplace(accountName, accountName);
					if (playerEmplace.second) {
						Player& player = playerEmplace.first->second;
						loadKPs(linked, player.killproofs);
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
			if (status == LoadingStatus::LoadingById && manuallyAdded) {
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

			cs.clear();

			cs.append(this->username);
			cs.append(": ");
			cs.append(" -- ");
			cs.append(std::to_string(response.status_code));
			cs.append(" -- ");
			cs.append(response.text);

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

void Player::loadKPs(nlohmann::json& json, Killproofs& storage) {
	auto tokens = json.at("tokens");
	// when field is null, data is not available
	if (tokens.is_null()) {
		// set all tokens fields to -1
		storage.setAllTokensFieldsToBlocked();
	}
	// else it is an array (can be empty)
	else if (tokens.is_array()) {
		for (auto token : tokens) {
			auto id = token.at("id");
			if (id.is_string()) {
				storage.setAmountFromId(id.get<std::string>(), token.at("amount"));
			} else if (id.is_number_integer()) {
				storage.setAmountFromId(id.get<int>(), token.at("amount"));
			}
		}
	}

	auto killproofs = json.at("killproofs");
	// when field is null, data is not available
	if (killproofs.is_null()) {
		// set all killproof fields to -1
		storage.setAllKillproofFieldsToBlocked();
	}
	// else it is an array (can be empty)
	else if (killproofs.is_array()) {
		// track all used killproof IDs
		std::set<int> unUsedKPs = { 77302, 81743, 88485, 94020, 93781 };

		// iterate over all available killproofs
		for (auto killproof : killproofs) {
			int kpId = killproof.at("id").get<int>();
			unUsedKPs.erase(kpId);
			storage.setAmountFromId(kpId, killproof.at("amount"));
		}

		// set rest KPs to blocked
		for (int unUsedKP : unUsedKPs) {
			storage.setBlockedFromId(unUsedKP);
		}
	}
}
