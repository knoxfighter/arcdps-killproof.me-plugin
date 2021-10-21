#pragma once

#include <atomic>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "Player.h"
#include "extension/arcdps_structs.h"

typedef std::function<amountVal(const Killproof&)> kpFunction;

class KillproofUI {
public:
	std::atomic_bool needSort = false;

	void draw(bool* p_open, ImGuiWindowFlags flags);

private:
	static void openInBrowser(const char* username);
	bool drawRow(const Alignment& alignment, const SYSTEMTIME* joinTime, const char* username, const char* characterName, const char* killproofId, const std::atomic<LoadingStatus>& status,
		kpFunction killproofsFun, kpFunction coffersFun, kpFunction kpOverallFun, bool treeNode, bool isCommander);
	void drawTextRow(bool* open, const char* text, const char* username, const std::atomic<LoadingStatus>& status, bool treeNode);

	char userAddBuf[1024]{};
	ImGuiTable* table = nullptr;
};
