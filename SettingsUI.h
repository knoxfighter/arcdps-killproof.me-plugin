#pragma once
#include "Settings.h"

class SettingsUI
{
	char shortcut[64]{};
	char shortCutRealName[32]{};
	int cofferValue = settings.settings.cofferValue;
	
public:
	SettingsUI();

	void draw();
};

extern SettingsUI settingsUI;
