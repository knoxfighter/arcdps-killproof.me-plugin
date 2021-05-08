#pragma once

#include <map>
#include <mutex>
#include <vector>
#include <d3d9.h>

#include "Killproofs.h"
#include "imgui/imgui.h"

class Player;
class KillproofUI;
class Icon;

extern KillproofUI killproofUi;

extern std::vector<std::string> trackedPlayers;
extern std::mutex trackedPlayersMutex;
extern std::map<std::string, Player> cachedPlayers;
extern std::mutex cachedPlayersMutex;
extern IDirect3DDevice9* d3d9Device;
extern HMODULE self_dll;
extern std::map<Killproof, Icon> icons;
extern std::string selfAccountName;

typedef void(*e3_func_ptr)(const char* str);
extern e3_func_ptr arc_log_file;
extern e3_func_ptr arc_log;

void loadAllKillproofs();
void loadKillproofsSizeChecked(Player& player);
void loadKillproofs(Player& player);

inline bool fileExists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}
