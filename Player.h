#pragma once

#include <string>

#include "Killproofs.h"


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

	void loadKillproofs();
};
