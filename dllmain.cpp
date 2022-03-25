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
#include "unofficial_extras/Definitions.h"
#include "extension/arcdps_structs.h"
#include "extension/Icon.h" // this import is needed for the icons map
#include "extension/KeyBindHandler.h"
#include "extension/KeyInput.h"
#include "extension/Singleton.h"
#include "extension/Widgets.h"
#include "extension/Windows/PositioningComponent.h"
#include "extension/Windows/Demo/DemoWindow.h"

#include "imgui/imgui.h"

// globals
char* arcvers;
arcdps_exports arc_exports = {};
HMODULE arc_dll;
HMODULE self_dll;
IDirect3DDevice9* d3d9Device;
ID3D11Device* d3d11Device;
UINT directxVersion;

// define `extern`s of other files
SingletonManager g_singletonManagerInstance;
arc_export_func_u64 ARC_EXPORT_E6;
arc_export_func_u64 ARC_EXPORT_E7;
e3_func_ptr ARC_LOG_FILE;
e3_func_ptr ARC_LOG;

bool showSettings = false;
bool initFailed = false;
bool extrasLoaded = false;

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
		if (ImGuiEx::KeyCodeInputWndHandle(hWnd, uMsg, wParam, lParam)) {
			return 0;
		}

		if (KeyBindHandler::instance().Wnd(hWnd, uMsg, wParam, lParam)) {
			return 0;
		}

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
				const int vkey = (int)wParam;
				// GlobalObjects::UpdateArcExports();
				// close windows on escape press (return 0, so arc and gw2 are not processing this event)
				// bool& show_killproof = settings.getShowKillproof();
				// if (!arc_hide_all && vkey == VK_ESCAPE) {
				// 	// close killproof window with escape
				// 	if (arc_window_fastclose && !settings.getDisableEscClose() && show_killproof) {
				// 		show_killproof = false;
				// 		return 0;
				// 	}
				// }
				// toggle killproof window
				// if (io->KeysDown[arc_global_mod1] && io->KeysDown[arc_global_mod2] && vkey == settings.getKillProofKey() && !arc_hide_all) {
				// 	show_killproof = !show_killproof;
				// 	return 0;
				// }
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
				GlobalObjects::UpdateArcExports();
				if (!wParam) {
					io->KeysDown[GlobalObjects::ARC_GLOBAL_MOD1] = false;
					io->KeysDown[GlobalObjects::ARC_GLOBAL_MOD2] = false;
				}
				break;
			}
			// track current input language
			case WM_INPUTLANGCHANGE: {
				GlobalObjects::CURRENT_HKL = (HKL)lParam;
				break;
			}
			default:
				break;
		}
	} catch (const std::exception& e) {
		ARC_LOG_FILE("exception in mod_wnd");
		ARC_LOG_FILE(e.what());
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
						KillproofUI::instance().needSort = true;
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
		ARC_LOG_FILE(e.what());

		// create dump of params
		if (ev) {
			ARC_LOG_FILE("ev:\n");
			char event[sizeof(cbtevent)];
			memcpy(event, ev, sizeof(cbtevent));
			std::stringstream evss;
			for (size_t i = 0; i < sizeof(cbtevent); ++i) {
				evss << std::hex << (int)event[i];
			}
			evss << "\n";
			std::string evs = evss.str();
			ARC_LOG_FILE(evs.c_str());
		}

		if (src) {
			ARC_LOG_FILE("src:\n");
			char srcData[sizeof(ag)];
			memcpy(srcData, src, sizeof(ag));
			std::stringstream srcDatass;
			for (size_t i = 0; i < sizeof(ag); ++i) {
				srcDatass << std::hex << (int)srcData[i];
			}
			srcDatass << "\n";
			std::string srcDataS = srcDatass.str();
			ARC_LOG_FILE(srcDataS.c_str());

			if (src->name) {
				ARC_LOG_FILE("src->name:\n");
				ARC_LOG_FILE(src->name);
			}
		}

		if (dst) {
			ARC_LOG_FILE("dst:\n");
			char dstData[sizeof(ag)];
			memcpy(dstData, dst, sizeof(ag));
			std::stringstream dstDatass;
			for (size_t i = 0; i < sizeof(ag); ++i) {
				dstDatass << std::hex << (int)dstData[i];
			}
			dstDatass << "\n";
			std::string dstDataS = dstDatass.str();
			ARC_LOG_FILE(dstDataS.c_str());

			if (dst->name) {
				ARC_LOG_FILE("dst->name:\n");
				ARC_LOG_FILE(dst->name);
			}
		}
		throw e;
	}
	return 0;
}

uintptr_t mod_options() {
	settingsUI.Draw();

	return 0;
}

uintptr_t mod_windows(const char* windowname) {
	if (!windowname) {
		KillproofUI::instance().DrawOptionCheckbox();
#if _DEBUG
		DemoWindow::instance().DrawOptionCheckbox();
#endif
	}
	return 0;
}

bool lastFrameShow = false;

void ShowKillproof() {
	bool& showKillproof = Settings::instance().settings.showKillproof;
	if (!lastFrameShow && showKillproof) {
		loadAllKillproofs();
	}
	lastFrameShow = showKillproof;

	KillproofUI::instance().Draw(!GlobalObjects::CanMoveWindows() ? ImGuiWindowFlags_NoMove : 0);
}

uintptr_t mod_imgui(uint32_t not_charsel_or_loading) {
#if _DEBUG
	DemoWindow::instance().Draw();
#endif
	// try {
		// ImGui::ShowMetricsWindow();

		GlobalObjects::UPDATE_CHECKER->Draw();

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

	GlobalObjects::UPDATE_CHECKER = std::make_unique<UpdateChecker>();

	const auto& currentVersion = GlobalObjects::UPDATE_CHECKER->GetCurrentVersion(self_dll);

	try {
		// Setup iconLoader
		iconLoader.Setup(self_dll, d3d9Device, d3d11Device);

		// Clear old Files
		GlobalObjects::UPDATE_CHECKER->ClearFiles(self_dll);

		// check for new version on github
		if (currentVersion) {
			GlobalObjects::UPDATE_STATE = std::move(GlobalObjects::UPDATE_CHECKER->CheckForUpdate(self_dll, currentVersion.value(), "knoxfighter/arcdps-killproof.me-plugin", false));
		}

		Settings::instance().load();

		lang.readFromFile();

		// windows init
#if _DEBUG
		DemoWindow::instance().Init();
#endif
		KillproofUI::instance().Init();

	} catch (const std::exception& e) {
		loading_successful = false;
		error_message = "Error loading all icons: ";
		error_message.append(e.what());
	}

	arc_exports.imguivers = IMGUI_VERSION_NUM;
	arc_exports.out_name = KILLPROOF_ME_PLUGIN_NAME;
	const std::string& version = currentVersion ? GlobalObjects::UPDATE_CHECKER->GetVersionAsString(currentVersion.value()) : "Unknown";
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
extern "C" __declspec(dllexport) void* get_init_addr(char* arcversionstr, ImGuiContext* imguicontext, void* dxptr, HMODULE new_arcdll, void* mallocfn,
                                                     void* freefn, UINT dxver) {
	arcvers = arcversionstr;
	ImGui::SetCurrentContext(imguicontext);
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))mallocfn, (void (*)(void*, void*))freefn);

	arc_dll = new_arcdll;
	ARC_EXPORT_E6 = (arc_export_func_u64)GetProcAddress(arc_dll, "e6");
	ARC_EXPORT_E7 = (arc_export_func_u64)GetProcAddress(arc_dll, "e7");
	ARC_LOG_FILE = (e3_func_ptr)GetProcAddress(arc_dll, "e3");
	ARC_LOG = (e3_func_ptr)GetProcAddress(arc_dll, "e8");

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

	// install imgui hooks
	PositioningComponentImGuiHook::InstallHooks(imguicontext);

	return mod_init;
}

/* release mod -- return ignored */
uintptr_t mod_release() {
	// finish and clear updateState
	GlobalObjects::UPDATE_STATE->FinishPendingTasks();
	GlobalObjects::UPDATE_STATE.reset(nullptr);

	icons.clear();

	Settings::instance().unload();

#if _DEBUG
	lang.saveToFile();
#endif

	iconLoader.Shutdown();

	g_singletonManagerInstance.Shutdown();

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
			KillproofUI::instance().needSort = true;
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

void language_changed_callback(Language pNewLanguage) {
	GlobalObjects::CURRENT_LANGUAGE = pNewLanguage;
}

/**
 * here for backwardscompatible to unofficial extras API v1.
 * Can be removed after it has a proper release.
 */
typedef void (*SquadUpdateCallbackSignature)(const UserInfo* pUpdatedUsers, uint64_t pUpdatedUsersCount);
struct ExtrasSubscriberInfo
{
	// Null terminated name of the addon subscribing to the changes. Must be valid for the lifetime of the subcribing addon. Set to
	// nullptr if initialization fails
	const char* SubscriberName = nullptr;

	// Called whenever anything in the squad changes. Only the users that changed are sent. If a user is removed from
	// the squad, it will be sent with Role == UserRole::None
	SquadUpdateCallbackSignature SquadUpdateCallback = nullptr;
};

extern "C" __declspec(dllexport) void arcdps_unofficial_extras_subscriber_init(const ExtrasAddonInfo* pExtrasInfo, void* pSubscriberInfo) {
	extrasLoaded = true;

	// do not subscribe, if initialization called from arcdps failed.
	if (initFailed) {
		return;
	}

	if (pExtrasInfo->ApiVersion == 1) {
		// V1 of the unofficial extras API, treat is as that!
		ExtrasSubscriberInfo* extrasSubscriberInfo = static_cast<ExtrasSubscriberInfo*>(pSubscriberInfo);

		if (selfAccountName.empty()) {
			selfAccountName = pExtrasInfo->SelfAccountName;
			if (selfAccountName.at(0) == ':')
				selfAccountName.erase(0, 1);
		}

		extrasSubscriberInfo->SubscriberName = KILLPROOF_ME_PLUGIN_NAME;
		extrasSubscriberInfo->SquadUpdateCallback = squad_update_callback;
	}
	// MaxInfoVersion has to be higher to have enough space to hold this object
	else if (pExtrasInfo->ApiVersion == 2 && pExtrasInfo->MaxInfoVersion >= 1) {
		ExtrasSubscriberInfoV1* subscriberInfo = static_cast<ExtrasSubscriberInfoV1*>(pSubscriberInfo);

		if (selfAccountName.empty()) {
			selfAccountName = pExtrasInfo->SelfAccountName;
			if (selfAccountName.at(0) == ':')
				selfAccountName.erase(0, 1);
		}

		subscriberInfo->SubscriberName = KILLPROOF_ME_PLUGIN_NAME;
		subscriberInfo->SquadUpdateCallback = squad_update_callback;
		subscriberInfo->LanguageChangedCallback = language_changed_callback;
	}
}
