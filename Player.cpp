#include "Player.h"

#include <cpr/cpr.h>
#include "parson/parson.h"

void Player::loadKillproofs() {
	std::string link("https://killproof.me/api/kp/");
	link.append(username);
	link.append("?lang=en");
	auto callback = cpr::GetCallback([this](cpr::Response r) {
		if (r.status_code == 200) {
			// load the json response
			JSON_Value* rootValue = json_parse_string(r.text.c_str());
			JSON_Object* rootObject = json_value_get_object(rootValue);

			JSON_Array* tokens = json_object_get_array(rootObject, "tokens");
			for (size_t i = 0; i < json_array_get_count(tokens); i++) {
				JSON_Object* tokenObject = json_array_get_object(tokens, i);
				const char* tokenId = json_object_get_string(tokenObject, "id");
				const double amount = json_object_get_number(tokenObject, "amount");
				this->killproofs.setAmountFromId(tokenId, amount);
			}

			JSON_Array* killproofs = json_object_get_array(rootObject, "killproofs");
			for (size_t i = 0; i < json_array_get_count(killproofs); i++) {
				JSON_Object* killProofObject = json_array_get_object(killproofs, i);
				const double kpId = json_object_get_number(killProofObject, "id");
				const double amount = json_object_get_number(killProofObject, "amount");
				this->killproofs.setAmountFromId(std::to_string(static_cast<int>(kpId)), amount);
			}

			// free everything from parson (its a c library)
			json_value_free(rootValue);

			this->noDataAvailable = false;
		}
		else {
			this->noDataAvailable = true;
		}
	}, cpr::Url{ link });
}
