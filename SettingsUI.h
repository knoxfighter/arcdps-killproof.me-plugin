#pragma once

#include "Settings.h"
#include "imgui/imgui.h"

class SettingsUI
{
	char shortcut[64]{};
	char shortCutRealName[32]{};
	char blockedDataText[64]{};
	
public:
	SettingsUI();

	void draw();
	void alignmentSelectable(Alignment select_alignment, Settings& settings);
};

