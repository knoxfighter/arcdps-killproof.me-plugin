#pragma once

#include <atomic>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "Player.h"
#include "extension/arcdps_structs.h"

class KillproofUI {
public:
	std::atomic_bool needSort = false;

	void draw(bool* p_open, ImGuiWindowFlags flags);

private:
	static void openInBrowser(const char* username);
	bool drawRow(const Alignment& alignment, const char* username, const char* characterName, const std::atomic<LoadingStatus>& status,
	                          const Killproofs& killproofs, const Coffers& coffers, bool treeNode, bool isCommander);

	char userAddBuf[1024]{};
	ImGuiTable* table = nullptr;
};
