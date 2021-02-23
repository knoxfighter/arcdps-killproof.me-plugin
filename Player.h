#pragma once

#include <string>

#include "arcdps_structs.h"
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
	std::atomic<LoadingStatus> status {LoadingStatus::NotLoaded};
	std::string errorMessage;

	void loadKillproofs();
};
