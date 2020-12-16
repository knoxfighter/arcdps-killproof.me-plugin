#include "Player.h"

#include <cpr/cpr.h>

#include "json.hpp"

void Player::loadKillproofs() {
	std::string link("https://killproof.me/api/kp/");
	link.append(username);
	link.append("?lang=en");
	auto callback = cpr::GetCallback([this](cpr::Response r) {
		if (r.status_code == 200) {
			auto json = nlohmann::json::parse(r.text);
			auto tokens = json.at("tokens");
			if (tokens.type() == nlohmann::json::value_t::array) {
				for (auto token : tokens) {
					this->killproofs.setAmountFromId(token.at("id").get<std::string>(), token.at("amount"));
				}
			}

			auto killproofs = json.at("killproofs");
			if (killproofs.type() == nlohmann::json::value_t::array) {
				for (auto killproof : killproofs) {
					this->killproofs.setAmountFromId(killproof.at("id").get<int>(), killproof.at("amount"));
				}
			}

			this->noDataAvailable = false;
		}
		else {
			this->noDataAvailable = true;
		}
	}, cpr::Url{ link });
}
