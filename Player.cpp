#include "Player.h"

#include <cpr/cpr.h>

#include "json.hpp"

void Player::loadKillproofs(e3_func_ptr out) {
	std::string link("https://killproof.me/api/kp/");
	link.append(username);
	link.append("?lang=en");

	// download it in a new thread (fire and forget)
	std::thread cprCall([=]() {
		cpr::Response response = cpr::Get(cpr::Url{ link });

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
				for (auto killproof : killproofs) {
					this->killproofs.setAmountFromId(killproof.at("id").get<int>(), killproof.at("amount"));
				}
			}

			this->noDataAvailable = false;
		}
		// silently set, when user not found
		else if (response.status_code == 404) {
			this->noDataAvailable = true;
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
			out((char*)cs.c_str());
		}
	});
	// we want to run async completely, so just detach
	cprCall.detach();
}
