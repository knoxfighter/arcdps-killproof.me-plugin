#pragma once
#include <mutex>
#include <set>

#include "Player.h"

std::set<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;
