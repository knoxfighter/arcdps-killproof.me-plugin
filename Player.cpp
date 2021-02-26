#include "Player.h"

#include <set>
#include <cpr/cpr.h>
#include <cpr/util.h>

#include "global.h"
#include "json.hpp"
#include "KillproofUI.h"

void Player::loadKillproofs() {
	using namespace std::chrono_literals;

	// make sure this is not run twice
	// So we skip, if the players data is unavailable, already loading or successfully loaded
	LoadingStatus loadingStatus = status.load();
	if (loadingStatus == LoadingStatus::Loading || loadingStatus == LoadingStatus::NoDataAvailable || loadingStatus == LoadingStatus::Loaded)
		return;
	// not run if Loading cannot be set or loading status was previously something different
	if (!status.compare_exchange_strong(loadingStatus, LoadingStatus::Loading)) 
		return;
	
	std::string link = "https://killproof.me/api/kp/";
	link.append(cpr::util::urlEncode(username));
	link.append("?lang=en");

	// download it in a new thread (fire and forget)
	std::thread cprCall([this, link]() {
		cpr::Response response = cpr::Get(cpr::Url{ link }, cpr::Header{{"User-Agent", "arcdps-killproof.me-plugin"}});

		if (response.status_code == 200) {
			auto json = nlohmann::json::parse(response.text);

			// get kpid and accountname
			killproofId = json.at("kpid").get<std::string>();
			std::string accountname = json.at("account_name").get<std::string>();
			
			// replace the key in the global map, when kpid was used to create this player
			if (username == killproofId) {
				// lock the maps
				std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);

				// replace the key of the cache
				auto node = cachedPlayers.extract(username);
				node.key() = accountname;
				cachedPlayers.insert(std::move(node));

				// replace the player in tracked players
				std::replace(trackedPlayers.begin(), trackedPlayers.end(), username, accountname);
			}

			// set username AFTER the check, if it the same as the kpid
			username = accountname;
			
			auto tokens = json.at("tokens");
			// when field is null, data is not available
			if (tokens.type() == nlohmann::json::value_t::null) {
				// set all tokens fields to -1
				this->killproofs.setAllTokensFieldsToBlocked();
			}
			// else it is an array (can be empty)
			else if (tokens.type() == nlohmann::json::value_t::array) {
				for (auto token : tokens) {
					this->killproofs.setAmountFromId(token.at("id").get<std::string>(), token.at("amount"));
				}
			}

			auto killproofs = json.at("killproofs");
			// when field is null, data is not available
			if (killproofs.type() == nlohmann::json::value_t::null) {
				// set all killproof fields to -1
				this->killproofs.setAllKillproofFieldsToBlocked();
			}
			// else it is an array (can be empty)
			else if (killproofs.type() == nlohmann::json::value_t::array) {
				// track all used killproof IDs
				std::set<int> unUsedKPs = { 77302, 81743, 88485, 94020 };

				// iterate over all available killproofs
				for (auto killproof : killproofs) {
					int kpId = killproof.at("id").get<int>();
					unUsedKPs.erase(kpId);
					this->killproofs.setAmountFromId(kpId, killproof.at("amount"));
				}

				// set rest KPs to blocked
				for (int unUsedKP : unUsedKPs) {
					this->killproofs.setBlockedFromId(unUsedKP);
				}
			}

			this->status = LoadingStatus::Loaded;
		}
		// silently set, when user not found
		else if (response.status_code == 404) {
			this->status = LoadingStatus::NoDataAvailable;
			this->killproofs.setAllKillproofFieldsToBlocked();
			this->killproofs.setAllTokensFieldsToBlocked();

			// try again as charactername
			// https://killproof.me/api/character/Lucy%20Falkenauge/kp
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
			arc_log(cs.c_str());

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
	});

	// we want to run async completely, so just detach
	cprCall.detach();
}
