#pragma once

#include <map>
#include <mutex>
#include <vector>
#include <d3d9.h>

#include "Killproofs.h"
#include "Player.h"
#include "UpdateChecker.h"

#include "extension/UpdateCheckerBase.h"
#include "unofficial_extras/Definitions.h"

constexpr auto KILLPROOF_ME_PLUGIN_NAME = "killproof.me";

enum class AddedBy;
class Player;
class KillproofUI;

extern std::vector<std::string> trackedPlayers;
extern std::mutex trackedPlayersMutex;
extern std::map<std::string, Player> cachedPlayers;
extern std::mutex cachedPlayersMutex;
extern std::vector<std::string> instancePlayers;
extern std::mutex instancePlayersMutex;
extern HMODULE self_dll;
extern std::map<Killproof, UINT> icons;
extern std::string selfAccountName;
extern bool extrasLoaded;

void loadAllKillproofs();
void loadKillproofsSizeChecked(Player& player);
void loadKillproofs(Player& player);

inline bool fileExists(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

void removePlayer(const std::string& username, AddedBy addedByToDelete = AddedBy::Miscellaneous);
// void removePlayerInstance(const std::string& username);
// void removePlayerTracking(const std::string& username);
bool addPlayerTracking(const std::string& username);
bool addPlayerAll(const std::string& username);
bool addPlayerInstance(const std::string& username);

class GlobalObjects {
public:
	// Updating myself stuff
	static inline std::unique_ptr<UpdateChecker> UPDATE_CHECKER = nullptr;
	static inline std::unique_ptr<UpdateCheckerBase::UpdateState> UPDATE_STATE = nullptr;

	// arc keyboard modifier
	static inline DWORD ARC_GLOBAL_MOD1 = 0;
	static inline DWORD ARC_GLOBAL_MOD2 = 0;
	static inline DWORD ARC_GLOBAL_MOD_MULTI = 0;

	// Arc export Cache
	static inline bool ARC_HIDE_ALL = false;
	static inline bool ARC_PANEL_ALWAYS_DRAW = false;
	static inline bool ARC_MOVELOCK_ALTUI = false;
	static inline bool ARC_CLICKLOCK_ALTUI = false;
	static inline bool ARC_WINDOW_FASTCLOSE = false;

	// Arc helper functions
	static void UpdateArcExports();
	static bool ModsPressed();
	static bool CanMoveWindows();

	// other
	// TODO: fill with actual values and keep them up to date
	static inline Language CURRENT_LANGUAGE = Language::English;
	static inline HKL CURRENT_HKL;
};
