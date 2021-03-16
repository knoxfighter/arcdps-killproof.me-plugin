#pragma once

#include <string>

#include "Killproofs.h"

enum class LoadingStatus {
	NotLoaded, // loading was not yet tried
	KpMeError, // Error returned from kp.me
	NoDataAvailable, // User has no kp.me account or account is private
	Loaded, // Successful, all data available to use
	LoadingById, // Data is currently being loaded by accountname oder kpid
	LoadingByChar // Data is currently bering loaded by charactername
};

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
