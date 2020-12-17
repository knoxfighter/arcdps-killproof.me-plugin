#pragma once

#include <string>

#include "Killproofs.h"


typedef void(*e3_func_ptr)(char* str);

class Player {
public:
	Player(std::string username, std::string characterName)
		: username(std::move(username)),
		  characterName(std::move(characterName)) {
	}

	Player() = default;

	std::string username;
	std::string characterName;
	Killproofs killproofs;
	bool noDataAvailable = true;

	void loadKillproofs(e3_func_ptr out);
};
