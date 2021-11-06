// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstdint>
#include <d3d9.h>
#include <d3d11.h>
#include <mutex>
#include <ranges>
#include <sstream>
#include <string>
#include <wincodec.h>
#include <Windows.h>

#include "global.h"
#include "KillproofUI.h"
#include "Lang.h"
#include "Player.h"
#include "Settings.h"
#include "SettingsUI.h"
#include "UpdateChecker.h"
#include "extension/arcdps_extras_structs.h"
#include "extension/arcdps_structs.h"
#include "extension/Icon.h" // this import is needed for the icons map
#include "extension/Widgets.h"
#include "imgui/imgui.h"

// predefine some functions
void readArcExports();

// globals
char* arcvers;
arcdps_exports arc_exports = {};
HMODULE arc_dll;
HMODULE self_dll;
IDirect3DDevice9* d3d9Device;
ID3D11Device* d3d11Device;
UINT directxVersion;
bool showSettings = false;
bool initFailed = false;
bool extrasLoaded = false;

typedef uint64_t (*arc_export_func_u64)();
// arc options
arc_export_func_u64 arc_export_e6;
bool arc_hide_all = false;
bool arc_panel_always_draw = false;
bool arc_movelock_altui = false;
bool arc_clicklock_altui = false;
bool arc_window_fastclose = false;

// arc keyboard modifier
arc_export_func_u64 arc_export_e7;
DWORD arc_global_mod1 = 0;
DWORD arc_global_mod2 = 0;
DWORD arc_global_mod_multi = 0;

// arc add to log
e3_func_ptr arc_log_file;
e3_func_ptr arc_log;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			self_dll = hModule;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

/* window callback -- return is assigned to umsg (return zero to not be processed by arcdps or game) */
uintptr_t mod_wnd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	try {
		auto const io = &ImGui::GetIO();

		switch (uMsg) {
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				const int vkey = (int)wParam;
				io->KeysDown[vkey] = false;
				if (vkey == VK_CONTROL) {
					io->KeyCtrl = false;
				} else if (vkey == VK_MENU) {
					io->KeyAlt = false;
				} else if (vkey == VK_SHIFT) {
					io->KeyShift = false;
				}
				break;
			}
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN: {
				readArcExports();
				const int vkey = (int)wParam;
				// close windows on escape press (return 0, so arc and gw2 are not processing this event)
				bool& show_killproof = settings.getShowKillproof();
				if (!arc_hide_all && vkey == VK_ESCAPE) {
					// close killproof window with escape
					if (arc_window_fastclose && !settings.getDisableEscClose() && show_killproof) {
						show_killproof = false;
						return 0;
					}
				}
				// toggle killproof window
				if (io->KeysDown[arc_global_mod1] && io->KeysDown[arc_global_mod2] && vkey == settings.getKillProofKey() && !arc_hide_all) {
					show_killproof = !show_killproof;
					return 0;
				}
				if (vkey == VK_CONTROL) {
					io->KeyCtrl = true;
				} else if (vkey == VK_MENU) {
					io->KeyAlt = true;
				} else if (vkey == VK_SHIFT) {
					io->KeyShift = true;
				}
				io->KeysDown[vkey] = true;
				break;
			}
			case WM_ACTIVATEAPP: {
				if (!wParam) {
					io->KeysDown[arc_global_mod1] = false;
					io->KeysDown[arc_global_mod2] = false;
				}
				break;
			}
			default:
				break;
		}
	} catch (const std::exception& e) {
		arc_log_file(e.what());
		throw e;
	}

	return uMsg;
}

/* combat callback -- may be called asynchronously. return ignored */
/* one participant will be party/squad, or minion of. no spawn statechange events. despawn statechange only on marked boss npcs */
uintptr_t mod_combat(cbtevent* ev, ag* src, ag* dst, const char* skillname, uint64_t id, uint64_t revision) {
	try {
		/* ev is null. dst will only be valid on tracking add. skillname will also be null */
		if (!ev) {
			/* notify tracking change */
			if (!src->elite) {
				// only run, when names are set and not null
				if (src->name != nullptr && src->name[0] != '\0' && dst->name != nullptr && dst->name[0] != '\0') {

					std::string username(dst->name);

					// remove ':' at the beginning of the name.
					if (username.at(0) == ':') {
						username.erase(0, 1);
					}

					/* add */
					if (src->prof) {
						std::scoped_lock<std::mutex, std::mutex, std::mutex> lock(cachedPlayersMutex, trackedPlayersMutex, instancePlayersMutex);

						// this is self
						if (selfAccountName.empty() && dst->self) {
							selfAccountName = username;
						}

						// add to tracking and instance
						addPlayerAll(username);

						auto playerIt = cachedPlayers.find(username);
						if (playerIt == cachedPlayers.end()) {
							// no element found, create it
							const auto& tryEmplace = cachedPlayers.try_emplace(username, username, AddedBy::Arcdps, dst->self, src->name, src->id);

							// check if emplacing successful, if yes, load the kp.me page
							if (tryEmplace.second) {
								// save player object to work on
								Player& player = tryEmplace.first->second;

								// load killproofs
								loadKillproofsSizeChecked(player);
							}
						} else {
							Player& player = playerIt->second;
							// update charactername
							player.characterName = src->name;
							if (player.addedBy == AddedBy::Manually || player.addedBy == AddedBy::Miscellaneous) {
								player.addedBy = AddedBy::Arcdps;
							}
							player.id = src->id;

							// load user data if not yet loaded (check inside function)
							loadKillproofsSizeChecked(player);

							if (player.addedBy == AddedBy::Arcdps && !player.self) {
								player.resetJoinedTime();
							}
						}

						// Tell the UI to resort, cause we added a player
						killproofUi.needSort = true;
					}
					/* remove */
					else {
						// do NOT remove yourself
						if (username != selfAccountName) {
							std::scoped_lock<std::mutex, std::mutex> guard(trackedPlayersMutex, instancePlayersMutex);

							// remove specific user
							removePlayer(username, AddedBy::Arcdps);
						}
					}
				}
			}
		} else {
			if (ev->is_statechange != CBTS_NONE) {
				if (ev->is_statechange == CBTS_TAG) {
					// some other person is tag now!
					uintptr_t id = src->id;
					for (auto& cachedPlayer : cachedPlayers | std::views::values) {
						if (cachedPlayer.id == id) {
							cachedPlayer.commander = true;
						} else {
							cachedPlayer.commander = false;
						}
					}
				}
			}
		}
	} catch (const std::exception& e) {
		arc_log_file(e.what());

		// create dump of params
		if (ev) {
			arc_log_file("ev:\n");
			char event[sizeof(cbtevent)];
			memcpy(event, ev, sizeof(cbtevent));
			std::stringstream evss;
			for (size_t i = 0; i < sizeof(cbtevent); ++i) {
				evss << std::hex << (int)event[i];
			}
			evss << "\n";
			std::string evs = evss.str();
			arc_log_file(evs.c_str());
		}

		if (src) {
			arc_log_file("src:\n");
			char srcData[sizeof(ag)];
			memcpy(srcData, src, sizeof(ag));
			std::stringstream srcDatass;
			for (size_t i = 0; i < sizeof(ag); ++i) {
				srcDatass << std::hex << (int)srcData[i];
			}
			srcDatass << "\n";
			std::string srcDataS = srcDatass.str();
			arc_log_file(srcDataS.c_str());

			if (src->name) {
				arc_log_file("src->name:\n");
				arc_log_file(src->name);
			}
		}

		if (dst) {
			arc_log_file("dst:\n");
			char dstData[sizeof(ag)];
			memcpy(dstData, dst, sizeof(ag));
			std::stringstream dstDatass;
			for (size_t i = 0; i < sizeof(ag); ++i) {
				dstDatass << std::hex << (int)dstData[i];
			}
			dstDatass << "\n";
			std::string dstDataS = dstDatass.str();
			arc_log_file(dstDataS.c_str());

			if (dst->name) {
				arc_log_file("dst->name:\n");
				arc_log_file(dst->name);
			}
		}
		throw e;
	}
	return 0;
}

uintptr_t mod_options() {
	settingsUI.draw();

	return 0;
}

uintptr_t mod_windows(const char* windowname) {
	if (!windowname) {
		bool& showKillproof = settings.getShowKillproof();
		ImGui::Checkbox(lang.translate(LangKey::SubMenuKp).c_str(), &showKillproof);
	}
	return 0;
}

bool modsPressed() {
	auto io = &ImGui::GetIO();

	return io->KeysDown[arc_global_mod1] && io->KeysDown[arc_global_mod2];
}

bool canMoveWindows() {
	if (!arc_movelock_altui) {
		return true;
	} else {
		return modsPressed();
	}
}

bool lastFrameShow = false;

void ShowKillproof() {
	bool& showKillproof = settings.getShowKillproof();
	if (!lastFrameShow && showKillproof) {
		loadAllKillproofs();
	}
	lastFrameShow = showKillproof;
	if (showKillproof) {
		killproofUi.draw(&showKillproof, (!canMoveWindows() ? ImGuiWindowFlags_NoMove : 0));
	}
}

void readArcExports() {
	uint64_t e6_result = arc_export_e6();
	uint64_t e7_result = arc_export_e7();

	arc_hide_all = (e6_result & 0x01);
	arc_panel_always_draw = (e6_result & 0x02);
	arc_movelock_altui = (e6_result & 0x04);
	arc_clicklock_altui = (e6_result & 0x08);
	arc_window_fastclose = (e6_result & 0x10);


	uint16_t* ra = (uint16_t*)&e7_result;
	if (ra) {
		arc_global_mod1 = ra[0];
		arc_global_mod2 = ra[1];
		arc_global_mod_multi = ra[2];
	}
}

uintptr_t mod_imgui(uint32_t not_charsel_or_loading) {
	// try {
		// ImGui::ShowMetricsWindow();

		updateChecker.Draw();

		if (!not_charsel_or_loading) return 0;
		ShowKillproof();
	// } catch (const std::exception& e) {
	// 	arc_log_file(e.what());
	// 	throw e;
	// }

	return 0;
}

/* initialize mod -- return table that arcdps will use for callbacks */
arcdps_exports* mod_init() {
	bool loading_successful = true;
	std::string error_message = "Unknown error";
	// load images
	try {
		// Setup iconLoader
		iconLoader.Setup(self_dll, d3d9Device, d3d11Device);

		// check for new version on github
		const auto& currentVersion = UpdateCheckerBase::GetCurrentVersion(self_dll);
		if (currentVersion) {
			updateChecker.CheckForUpdate(currentVersion.value(), "knoxfighter/arcdps-killproof.me-plugin", false);
		}

		UpdateCheckerBase::ClearFiles(self_dll);

		settings.load();

		lang.readFromFile();
	} catch (const std::exception& e) {
		loading_successful = false;
		error_message = "Error loading all icons: ";
		error_message.append(e.what());
	}

	arc_exports.imguivers = IMGUI_VERSION_NUM;
	arc_exports.out_name = KILLPROOF_ME_PLUGIN_NAME;
	const std::string& version = UpdateCheckerBase::GetVersionAsString(self_dll);
	char* version_c_str = new char[version.length() + 1];
	strcpy_s(version_c_str, version.length() + 1, version.c_str());
	arc_exports.out_build = version_c_str;

	if (loading_successful) {
		/* for arcdps */
		arc_exports.sig = 0x6BAF1938;
		arc_exports.size = sizeof(arcdps_exports);
		arc_exports.wnd_nofilter = mod_wnd;
		arc_exports.combat = mod_combat;
		arc_exports.imgui = mod_imgui;
		arc_exports.options_end = mod_options;
		arc_exports.options_windows = mod_windows;
	} else {
		initFailed = true;
		arc_exports.sig = 0;
		const std::string::size_type size = error_message.size();
		char* buffer = new char[size + 1]; //we need extra char for NUL
		memcpy(buffer, error_message.c_str(), size + 1);
		arc_exports.size = (uintptr_t)buffer;

		icons.clear();
	}
	return &arc_exports;
}

/* export -- arcdps looks for this exported function and calls the address it returns on client load */
extern "C" __declspec(dllexport) void* get_init_addr(char* arcversionstr, void* imguicontext, void* dxptr, HMODULE new_arcdll, void* mallocfn,
                                                     void* freefn, UINT dxver) {
	arcvers = arcversionstr;
	ImGui::SetCurrentContext(static_cast<ImGuiContext*>(imguicontext));
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))mallocfn, (void (*)(void*, void*))freefn);

	arc_dll = new_arcdll;
	arc_export_e6 = (arc_export_func_u64)GetProcAddress(arc_dll, "e6");
	arc_export_e7 = (arc_export_func_u64)GetProcAddress(arc_dll, "e7");
	arc_log_file = (e3_func_ptr)GetProcAddress(arc_dll, "e3");
	arc_log = (e3_func_ptr)GetProcAddress(arc_dll, "e8");

	// dx11 not available in older arcdps versions
	std::string arcVersion = arcversionstr;
	auto firstDot = arcVersion.find_first_of('.');
	arcVersion = arcVersion.substr(0, firstDot);
	int arcVersionNum = std::stoi(arcVersion);
	if (arcVersionNum > 20210828 && dxver == 11) {
		auto swapChain = static_cast<IDXGISwapChain*>(dxptr);
		swapChain->GetDevice(__uuidof(d3d11Device), reinterpret_cast<void**>(&d3d11Device));
		directxVersion = 11;
	} else {
		d3d9Device = static_cast<IDirect3DDevice9*>(dxptr);
		directxVersion = 9;
	}

	return mod_init;
}

/* release mod -- return ignored */
uintptr_t mod_release() {
	icons.clear();

	settings.unload();

#if _DEBUG
	lang.saveToFile();
#endif

	iconLoader.Shutdown();

	return 0;
}

/* export -- arcdps looks for this exported function and calls the address it returns on client exit */
extern "C" __declspec(dllexport) void* get_release_addr() {
	arcvers = nullptr;
	return mod_release;
}

void squad_update_callback(const UserInfo* updatedUsers, size_t updatedUsersCount) {
	std::scoped_lock<std::mutex, std::mutex, std::mutex> guard(trackedPlayersMutex, instancePlayersMutex, cachedPlayersMutex);

	for (size_t i = 0; i < updatedUsersCount; i++) {
		std::string username = updatedUsers[i].AccountName;

		// remove ':' at the beginning of the name.
		if (username.at(0) == ':') {
			username.erase(0, 1);
		}

		if (updatedUsers[i].Role != UserRole::None) // User added/updated
		{
			// add to tracking
			// addPlayerTracking(username);
			if (!addPlayerAll(username)) {
				// player already tracked, do nothing
				continue;
			}

			auto playerIt = cachedPlayers.find(username);
			if (playerIt == cachedPlayers.end()) {
				// no element found, create it
				const auto& tryEmplace = cachedPlayers.try_emplace(username, username, AddedBy::Extras, username == selfAccountName);

				// check if emplacing successful, if yes, load the kp.me page
				if (tryEmplace.second) {
					// save player object to work on
					Player& player = tryEmplace.first->second;

					// load killproofs
					loadKillproofsSizeChecked(player);
				}
			} else {
				// load user data if not yet loaded (check inside function)
				loadKillproofsSizeChecked(playerIt->second);

				// This player was added automatically
				playerIt->second.addedBy = AddedBy::Extras;

				// update joined data
				if (!playerIt->second.self) {
					playerIt->second.resetJoinedTime();
				}
			}

			// Tell the UI to resort, cause we added a player
			killproofUi.needSort = true;
		} else // User removed
		{
			if (username == selfAccountName) {
				auto pred = [](const std::string& player) {
					if (player == selfAccountName) return false;
					const auto& cachedIt = cachedPlayers.find(player);
					if (cachedIt != cachedPlayers.end()) {
						return cachedIt->second.addedBy != AddedBy::Manually;
					}

					return false;
				};
				// Yourself got removed, you have left the squad/group
				// remove all other players, except yourself
				const auto& trackedSub = std::ranges::remove_if(trackedPlayers, pred);
				trackedPlayers.erase(trackedSub.begin(), trackedSub.end());

				const auto& instanceSub = std::ranges::remove_if(instancePlayers, pred);
				instancePlayers.erase(instanceSub.begin(), instanceSub.end());
			} else {
				removePlayer(username, AddedBy::Extras);
			}
		}
	}
}

extern "C" __declspec(dllexport) void arcdps_unofficial_extras_subscriber_init(const ExtrasAddonInfo* pExtrasInfo, ExtrasSubscriberInfo* pSubscriberInfo) {
	extrasLoaded = true;

	if (pExtrasInfo->ApiVersion != 1) {
		// incompatible extra API version, do not subscribe and show error
		return;
	}

	// do not subscribe, if initialization called from arcdps failed.
	if (initFailed) {
		return;
	}

	if (selfAccountName.empty()) {
		selfAccountName = pExtrasInfo->SelfAccountName;
		if (selfAccountName.at(0) == ':')
			selfAccountName.erase(0, 1);
	}

	pSubscriberInfo->SubscriberName = KILLPROOF_ME_PLUGIN_NAME;
	pSubscriberInfo->SquadUpdateCallback = squad_update_callback;
}
