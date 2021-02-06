#pragma once

#include "imgui/imgui.h"

class SettingsUI
{
	char shortcut[64]{};
	char shortCutRealName[32]{};
	char blockedDataText[64]{};
	
public:
	SettingsUI();

	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};

