#pragma once

#include <map>
#include <mutex>
#include <vector>

class Player;
class KillproofUI;

extern KillproofUI killproofUi;

extern std::vector<std::string> trackedPlayers;
extern std::mutex trackedPlayersMutex;
extern std::map<std::string, Player> cachedPlayers;
extern std::mutex cachedPlayersMutex;

typedef void(*e3_func_ptr)(const char* str);
extern e3_func_ptr arc_log;

void loadKillproofsSizeChecked(Player& player);
