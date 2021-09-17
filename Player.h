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

enum class AddedBy {
	Manually,
	Arcdps,
	Extras,
	Miscellaneous,
};

class Player {
public:
	Player(std::string username, AddedBy addedBy, std::string characterName = "", uintptr_t id = 0)
		: username(std::move(username)),
		  characterName(std::move(characterName)),
		  id(id),
		  addedBy(addedBy) {
		resetJoinedTime();
	}

	Player() = default;

	uintptr_t id;
	std::string username;
	std::string characterName;
	std::string killproofId;
	std::atomic<LoadingStatus> status{LoadingStatus::NotLoaded};
	std::string errorMessage;
	AddedBy addedBy;
	std::vector<std::string> linkedAccounts;
	bool commander = false;
	std::optional<Killproofs> linkedTotalKillproofs;
	__time64_t joinedTime;

	void resetJoinedTime() {
		const auto& systime = std::chrono::system_clock::now();
		joinedTime = std::chrono::system_clock::to_time_t(systime);
	}

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
