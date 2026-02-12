#include "global.h"

#include <map>
#include <mutex>
#include <vector>

#include "ArcdpsExtension/IconLoader.h"
#include "KillproofUI.h"
#include "Player.h"
#include "resource.h"
#include "Settings.h"

#include "ArcdpsExtension/arcdps_structs.h"

#include <imgui/imgui.h>

std::vector<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;
std::vector<std::string> instancePlayers;
std::mutex instancePlayersMutex;
std::string selfAccountName;
bool extrasLoaded = false;
uint32_t currentMap = 0;

void loadAllKillproofs() {
	if (trackedPlayers.size() <= 10 && Settings::instance().settings.showKillproof) {
		for (const std::string& trackedPlayer : trackedPlayers) {
			Player& player = cachedPlayers.at(trackedPlayer);
			if (player.status == LoadingStatus::NotLoaded) {
				player.loadKillproofs();
			}
		}
	}
}

/**
 * Do not load, when more than 10 players are in your squad, we are not interested in open world stuff
 */
void loadKillproofsSizeChecked(Player& player) {
	if (trackedPlayers.size() <= 10) {
		loadKillproofs(player);
	}
}

/**
 * Only load, when not already loading
 * Also do NOT load if the killproof.me window is hidden. We can skip loading, when the user is not interested what the results are.
 */
void loadKillproofs(Player& player) {
	if (player.status == LoadingStatus::NotLoaded && Settings::instance().settings.showKillproof) {
		player.loadKillproofs();
	}
}

/**
 * lock `trackedPlayersMutex` and `instancePlayersMutex` before calling this
 */
void removePlayer(const Player& pPlayer, AddedBy pAddedByToDelete) {
	// check if it should be removed
	if (pAddedByToDelete == AddedBy::Miscellaneous || pPlayer.addedBy == pAddedByToDelete) {
		// actually remove from tracking
		const auto& trackedSub = std::ranges::remove(trackedPlayers, pPlayer.username);
		trackedPlayers.erase(trackedSub.begin(), trackedSub.end());

		const auto& instanceSub = std::ranges::remove(instancePlayers, pPlayer.username);
		instancePlayers.erase(instanceSub.begin(), instanceSub.end());
	}
}

/**
 * lock `trackedPlayersMutex` and `instancePlayersMutex` before calling this
 */
void removePlayer(uintptr_t pId, AddedBy pAddedByToDelete) {
	const auto& playerIt = std::ranges::find_if(cachedPlayers, [pId](const auto& pPlayer) {
		return pPlayer.second.id == pId;
	});

	if (playerIt != cachedPlayers.end()) {
		removePlayer(playerIt->second, pAddedByToDelete);
	}
}

/**
 * lock `trackedPlayersMutex` and `instancePlayersMutex` before calling this
 */
void removePlayer(const std::string& username, AddedBy addedByToDelete) {
	// remove specific user
	auto pred = [&username, addedByToDelete](const std::string& player) {
		if (username == player) {
			if (addedByToDelete == AddedBy::Miscellaneous) {
				return true;
			}
			const auto& cachedPlayerIt = cachedPlayers.find(player);
			if (cachedPlayerIt != cachedPlayers.end()) {
				return cachedPlayerIt->second.addedBy == addedByToDelete;
			}
		}

		return false;
	};

	// actually remove from tracking
	const auto& trackedSub = std::ranges::remove_if(trackedPlayers, pred);
	trackedPlayers.erase(trackedSub.begin(), trackedSub.end());

	const auto& instanceSub = std::ranges::remove_if(instancePlayers, pred);
	instancePlayers.erase(instanceSub.begin(), instanceSub.end());
}

/**
 * lock `trackedPlayersMutex` and `instancePlayersMutex` before calling this
 */
bool addPlayerAll(const std::string& username) {
	addPlayerInstance(username);
	return addPlayerTracking(username);
}

/**
 * add to this-instance players
 * only add to tracking, if not already there
 *
 * lock `instancePlayersMutex` before calling this
 */
bool addPlayerInstance(const std::string& username) {
	if (std::ranges::find(instancePlayers, username) == instancePlayers.end()) {
		instancePlayers.emplace_back(username);
		return true;
	}
	return false;
}

/**
 * add to tracking
 * only add to tracking, if not already there
 * 
 * lock `trackedPlayersMutex` before calling this
 */
bool addPlayerTracking(const std::string& username) {
	if (std::ranges::find(trackedPlayers, username) == trackedPlayers.end()) {
		trackedPlayers.emplace_back(username);
		return true;
	}
	return false;
}

/**
 *
 * lock `cachedPlayersMutex` before calling this!
 */
void updateCommander(const std::string& commanderName) {
	for (auto& cachedPlayer : cachedPlayers) {
		Player& player = cachedPlayer.second;
		if (player.username == commanderName) {
			player.commander = true;
		} else {
			player.commander = false;
		}
	}
}

void GlobalObjects::UpdateArcExports() {
	uint64_t e6_result = ARC_EXPORT_E6();
	uint64_t e7_result = ARC_EXPORT_E7();

	ARC_HIDE_ALL = (e6_result & 0x01);
	ARC_PANEL_ALWAYS_DRAW = (e6_result & 0x02);
	ARC_MOVELOCK_ALTUI = (e6_result & 0x04);
	ARC_CLICKLOCK_ALTUI = (e6_result & 0x08);
	ARC_WINDOW_FASTCLOSE = (e6_result & 0x10);


	uint16_t* ra = (uint16_t*)&e7_result;
	if (ra) {
		ARC_GLOBAL_MOD1 = ra[0];
		ARC_GLOBAL_MOD2 = ra[1];
		ARC_GLOBAL_MOD_MULTI = ra[2];
	}
}

bool GlobalObjects::ModsPressed() {
	auto io = &ImGui::GetIO();

	return io->KeysDown[ARC_GLOBAL_MOD1] && io->KeysDown[ARC_GLOBAL_MOD2];
}

bool GlobalObjects::CanMoveWindows() {
	if (!ARC_MOVELOCK_ALTUI) {
		return true;
	} else {
		return ModsPressed();
	}
}
