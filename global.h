#pragma once

#include <map>
#include <mutex>
#include <set>

class Player;

extern std::set<std::string> trackedPlayers;
extern std::mutex trackedPlayersMutex;
extern std::map<std::string, Player> cachedPlayers;
extern std::mutex cachedPlayersMutex;

typedef void(*e3_func_ptr)(char* str);
extern e3_func_ptr arc_log;
