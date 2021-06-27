#pragma once

#include <optional>
#include <string>

#include "Coffers.h"
#include "Killproofs.h"
#include "Settings.h"
#include "extension/json.hpp"

enum class LoadingStatus {
	NotLoaded,
	// loading was not yet tried
	KpMeError,
	// Error returned from kp.me
	NoDataAvailable,
	// User has no kp.me account or account is private
	Loaded,
	// Successful, all data available to use
	LoadingById,
	// Data is currently being loaded by accountname oder kpid
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
	std::atomic<LoadingStatus> status{LoadingStatus::NotLoaded};
	std::string errorMessage;
	bool manuallyAdded = false;
	std::vector<std::string> linkedAccounts;
	bool commander = false;
	std::optional<Killproofs> linkedTotalKillproofs;

	void loadKillproofs();
	amountVal getKillproofs(const Killproof& kp) const {
		return killproofs.getAmount(kp);
	}
	amountVal getCoffers(const Killproof& kp) const {
		return coffers.getAmount(kp);
	}
	amountVal getKpOverall(const Killproof& kp) const;

	amountVal getKillproofsTotal(const Killproof& kp) const;
	amountVal getCoffersTotal(const Killproof& kp) const;
	amountVal getKpOverallTotal(const Killproof& kp) const;
	
	static void loadKPs(nlohmann::json& json, Killproofs& killproofStorage, Coffers& cofferStorage);

private:
	Killproofs killproofs;
	Coffers coffers;
	std::optional<Coffers> linkedTotalCoffers;
};
