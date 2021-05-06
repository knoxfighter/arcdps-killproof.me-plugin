#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

class WindowSettingsUI {
public:
	WindowSettingsUI();
	void draw(ImGuiTable* table);

private:
	char blockedDataText[64]{};
};

extern WindowSettingsUI windowSettingsUI;
