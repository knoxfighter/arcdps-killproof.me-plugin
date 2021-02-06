#include <map>
#include <mutex>
#include <vector>

#include "KillproofUI.h"
#include "Player.h"

std::vector<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;
KillproofUI killproofUi;