#include "global.h"

#include <map>
#include <mutex>
#include <vector>

#include "extension/Icon.h"
#include "KillproofUI.h"
#include "Player.h"
#include "Settings.h"

std::vector<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;
KillproofUI killproofUi;
std::map<Killproof, Icon> icons;
std::string selfAccountName;

void loadAllKillproofs() {
	if (trackedPlayers.size() <= 10 && settings.getShowKillproof()) {
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
	if (player.status == LoadingStatus::NotLoaded && settings.getShowKillproof()) {
		player.loadKillproofs();
	}
}
