// dllmain.cpp : Defines the entry point for the DLL application.
#include <cstdint>
#include <d3d9.h>
#include <mutex>
#include <sstream>
#include <string>
#include <wincodec.h>
#include <Windows.h>

#include "global.h"
#include "KillproofUI.h"
#include "Lang.h"
#include "Player.h"
#include "resource.h"
#include "Settings.h"
#include "SettingsUI.h"
#include "UpdateChecker.h"
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
bool showSettings = false;

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
		case WM_SYSKEYUP:
			{
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
		case WM_SYSKEYDOWN:
			{
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
		case WM_ACTIVATEAPP:
			{
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
						std::scoped_lock<std::mutex, std::mutex> lock(cachedPlayersMutex, trackedPlayersMutex);

						// if this is the first player, it is me
						if (selfAccountName.empty() && src->id == 2000) {
							selfAccountName = username;
						}

						// add to tracking
						// only add to tracking, if not already there
						if (std::find(trackedPlayers.begin(), trackedPlayers.end(), username) == trackedPlayers.end()) {
							trackedPlayers.emplace_back(username);
						}
							
						auto playerIt = cachedPlayers.find(username);
						if (playerIt == cachedPlayers.end()) {
							// no element found, create it
							const auto& tryEmplace = cachedPlayers.try_emplace(username, username, src->name);

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
							player.manuallyAdded = false;

							// load user data if not yet loaded (check inside function)
							loadKillproofsSizeChecked(player);
						}

						// Tell the UI to resort, cause we added a player
						killproofUi.needSort = true;
					}
						/* remove */
					else {
						std::lock_guard<std::mutex> guard(trackedPlayersMutex);
						trackedPlayers.erase(std::remove(trackedPlayers.begin(), trackedPlayers.end(), username), trackedPlayers.end());
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
	ImGuiEx::BeginMenu(lang.translate(LangKey::SettingsWindowName).c_str(), []() {
		settingsUI.draw();
	});

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
	try {
		ImGui::ShowDemoWindow();
		if (!not_charsel_or_loading) return 0;
		ShowKillproof();

		updateChecker.Draw();
	} catch (const std::exception& e) {
		arc_log_file(e.what());
		throw e;
	}

	return 0;
}

void load_images() {
	icons.try_emplace(Killproof::li, ID_LI, self_dll, d3d9Device);
	icons.try_emplace(Killproof::ld, ID_LD, self_dll, d3d9Device);
	icons.try_emplace(Killproof::liLd, ID_LILD, self_dll, d3d9Device);
	icons.try_emplace(Killproof::vg, ID_VG, self_dll, d3d9Device);
	icons.try_emplace(Killproof::gorse, ID_Gorse, self_dll, d3d9Device);
	icons.try_emplace(Killproof::sabetha, ID_Sabetha, self_dll, d3d9Device);
	icons.try_emplace(Killproof::sloth, ID_Sloth, self_dll, d3d9Device);
	icons.try_emplace(Killproof::matthias, ID_Matt, self_dll, d3d9Device);
	icons.try_emplace(Killproof::escort, ID_Escort, self_dll, d3d9Device);
	icons.try_emplace(Killproof::kc, ID_KC, self_dll, d3d9Device);
	icons.try_emplace(Killproof::xera, ID_Xera, self_dll, d3d9Device);
	icons.try_emplace(Killproof::cairn, ID_Cairn, self_dll, d3d9Device);
	icons.try_emplace(Killproof::mo, ID_MO, self_dll, d3d9Device);
	icons.try_emplace(Killproof::samarog, ID_Samarog, self_dll, d3d9Device);
	icons.try_emplace(Killproof::deimos, ID_Deimos, self_dll, d3d9Device);
	icons.try_emplace(Killproof::desmina, ID_Desmina, self_dll, d3d9Device);
	icons.try_emplace(Killproof::river, ID_River, self_dll, d3d9Device);
	icons.try_emplace(Killproof::statues, ID_Statues, self_dll, d3d9Device);
	icons.try_emplace(Killproof::dhuum, ID_Dhuum, self_dll, d3d9Device);
	icons.try_emplace(Killproof::ca, ID_CA, self_dll, d3d9Device);
	icons.try_emplace(Killproof::twins, ID_Twins, self_dll, d3d9Device);
	icons.try_emplace(Killproof::qadim, ID_Qadim1, self_dll, d3d9Device);
	icons.try_emplace(Killproof::adina, ID_Adina, self_dll, d3d9Device);
	icons.try_emplace(Killproof::sabir, ID_Sabir, self_dll, d3d9Device);
	icons.try_emplace(Killproof::qadim2, ID_Qadim2, self_dll, d3d9Device);
	icons.try_emplace(Killproof::uce, ID_UFE, self_dll, d3d9Device);
	icons.try_emplace(Killproof::ufe, ID_UFE, self_dll, d3d9Device);
}

/* initialize mod -- return table that arcdps will use for callbacks */
arcdps_exports* mod_init() {
	bool loading_successful = true;
	std::string error_message = "Unknown error";
	// load images
	try {
		// load images to ram
		load_images();

		// check for new version on github
		updateChecker.checkForUpdate(self_dll, "knoxfighter/arcdps-killproof.me-plugin");
	} catch (const std::exception& e) {
		loading_successful = false;
		error_message = "Error loading all icons: ";
		error_message.append(e.what());
	}

	// create my own directory :)
	// if (!(CreateDirectoryA("addons\\killproof.me\\", NULL) || ERROR_ALREADY_EXISTS == GetLastError())) {
	// 	loading_successful = false;
	// 	error_message = "Error creating my own directory: ";
	// 	error_message.append(std::to_string(GetLastError()));
	// }

	arc_exports.imguivers = IMGUI_VERSION_NUM;
	arc_exports.out_name = "killproof.me";
	arc_exports.out_build = UpdateCheckerBase::GetVersionAsString(self_dll);

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
extern "C" __declspec(dllexport) void* get_init_addr(char* arcversionstr, void* imguicontext, IDirect3DDevice9* id3dd9, HMODULE new_arcdll, void* mallocfn, void* freefn) {
	arcvers = arcversionstr;
	ImGui::SetCurrentContext(static_cast<ImGuiContext*>(imguicontext));
	ImGui::SetAllocatorFunctions((void* (*)(size_t, void*))mallocfn, (void (*)(void*, void*))freefn);

	arc_dll = new_arcdll;
	arc_export_e6 = (arc_export_func_u64)GetProcAddress(arc_dll, "e6");
	arc_export_e7 = (arc_export_func_u64)GetProcAddress(arc_dll, "e7");
	arc_log_file = (e3_func_ptr)GetProcAddress(arc_dll, "e3");
	arc_log = (e3_func_ptr)GetProcAddress(arc_dll, "e8");

	d3d9Device = id3dd9;

	return mod_init;
}

/* release mod -- return ignored */
uintptr_t mod_release() {
	icons.clear();
	return 0;
}

/* export -- arcdps looks for this exported function and calls the address it returns on client exit */
extern "C" __declspec(dllexport) void* get_release_addr() {
	arcvers = nullptr;
	return mod_release;
}
