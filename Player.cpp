#include "Player.h"

#include <set>
#include <cpr/cpr.h>
#include <cpr/util.h>

#include "global.h"
#include "json.hpp"
#include "KillproofUI.h"

void Player::loadKillproofs() {
	std::string link = "https://killproof.me/api/kp/";
	link.append(cpr::util::urlEncode(username));
	link.append("?lang=en");

	// download it in a new thread (fire and forget)
	std::thread cprCall([=]() {
		cpr::Response response = cpr::Get(cpr::Url{ link }, cpr::Header{{"User-Agent", "arcdps-killproof.me-plugin"}});

		if (response.status_code == 200) {
			auto json = nlohmann::json::parse(response.text);
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

			this->noDataAvailable = false;
		}
		// silently set, when user not found
		else if (response.status_code == 404) {
			this->noDataAvailable = true;
			this->killproofs.setAllKillproofFieldsToBlocked();
			this->killproofs.setAllTokensFieldsToBlocked();
		}
		// on any other error, print verbose output into the arcdps.log file
		else {
			this->noDataAvailable = true;

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
			arc_log((char*)cs.c_str());
		}

		// say UI to reload sorting
		killproofUi.needSort = true;
	});
	// we want to run async completely, so just detach
	cprCall.detach();
}
