#pragma once

#include "Coffers.h"
#include "Killproofs.h"

#include <optional>
#include <string>
#include <Windows.h>

#include <nlohmann/json.hpp>

enum class LoadingStatus {
	// loading was not yet tried
	NotLoaded,
	// Error returned from kp.me
	KpMeError,
	// User has no kp.me account or account is private
	NoDataAvailable,
	// Successful, all data available to use
	Loaded,
	// Data is currently being loaded by accountname oder kpid
	LoadingById,
	// Data is currently bering loaded by charactername
	LoadingByChar,
	// Data was loaded by a linked account name
	LoadedByLinked,
};

enum class AddedBy {
	Manually,
	Arcdps,
	Extras,
	Miscellaneous,
};

class Player {
public:
	Player(std::string username, AddedBy addedBy, bool self = false, std::string characterName = "", uintptr_t id = 0)
		: username(std::move(username)),
		  characterName(std::move(characterName)),
		  id(id),
		  addedBy(addedBy),
		  self(self) {
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
	SYSTEMTIME joinedTime;
	bool self = false;

	void resetJoinedTime() {
		GetLocalTime(&joinedTime);
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

	void LoadAll(const nlohmann::json& json);
	static void loadKPs(const nlohmann::json& json, Killproofs& killproofStorage, Coffers& cofferStorage);

private:
	Killproofs killproofs;
	Coffers coffers;
	std::optional<Coffers> linkedTotalCoffers;
};
