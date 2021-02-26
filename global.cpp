#include "global.h"

#include <map>
#include <mutex>
#include <vector>

#include "Icon.h"
#include "KillproofUI.h"
#include "Player.h"

std::vector<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;
KillproofUI killproofUi;
std::map<Killproof, Icon> icons;

void loadKillproofsSizeChecked(Player& player) {
	if (trackedPlayers.size() <= 10) {
		loadKillproofs(player);
	}
}

void loadKillproofs(Player& player) {
	if (player.status == LoadingStatus::NotLoaded) {
		player.loadKillproofs();
	}
}
