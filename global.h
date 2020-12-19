#pragma once
#include <map>
#include <mutex>
#include <set>

class Player;

std::set<std::string> trackedPlayers;
std::mutex trackedPlayersMutex;
std::map<std::string, Player> cachedPlayers;
std::mutex cachedPlayersMutex;

typedef void(*e3_func_ptr)(char* str);
extern e3_func_ptr arc_log;
