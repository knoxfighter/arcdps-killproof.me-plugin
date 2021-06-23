#pragma once

#include <optional>
#include <string>

#include "Coffers.h"
#include "Killproofs.h"
#include "extension/json.hpp"

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
	Player(std::string username, std::string characterName = "", uintptr_t id = 0, bool manuallyAdded = false)
		: username(std::move(username)),
		  characterName(std::move(characterName)),
		  id(id),
		  manuallyAdded(manuallyAdded) {
	}

	Player() = default;

	uintptr_t id;
	std::string username;
	std::string characterName;
	std::string killproofId;
	Killproofs killproofs;
	Coffers coffers;
	std::optional<Killproofs> linkedTotalKillproofs;
	std::optional<Coffers> linkedTotalCoffers;
	std::atomic<LoadingStatus> status{LoadingStatus::NotLoaded};
	std::string errorMessage;
	bool manuallyAdded = false;
	std::vector<std::string> linkedAccounts;
	bool commander = false;

	void loadKillproofs();
	static void loadKPs(nlohmann::json& json, Killproofs& killproofStorage, Coffers& cofferStorage);
};
