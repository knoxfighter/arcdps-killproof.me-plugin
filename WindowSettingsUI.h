#pragma once

#include "Settings.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

class WindowSettingsUI {
public:
	WindowSettingsUI();
	void draw(ImGuiTable* table, ImGuiWindow* currentRootWindow);

private:
	char blockedDataText[64]{};
	int position = static_cast<int>(settings.getPosition());
	int cornerPosition = static_cast<int>(settings.getCornerPosition());
	int selfPanelCornerPosition = static_cast<int>(settings.getSelfPanelCornerPosition());
	int anchorPanelCornerPosition = static_cast<int>(settings.getAnchorPanelCornerPosition());
};

extern WindowSettingsUI windowSettingsUI;
