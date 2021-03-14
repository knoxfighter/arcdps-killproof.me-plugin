#pragma once

#include <string>

#include "extension/arcdps_structs.h"
#include "Killproofs.h"

class Player {
public:
	Player(std::string username, std::string characterName, bool manuallyAdded = false)
		: username(std::move(username)),
		  characterName(std::move(characterName)),
		  manuallyAdded(std::move(manuallyAdded)) {
	}

	Player() = default;

	std::string username;
	std::string characterName;
	std::string killproofId;
	Killproofs killproofs;
	std::atomic<LoadingStatus> status{LoadingStatus::NotLoaded};
	std::string errorMessage;
	bool manuallyAdded = false;

	void loadKillproofs();
};
