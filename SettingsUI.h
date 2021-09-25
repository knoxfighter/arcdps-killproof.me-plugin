#pragma once
#include "Settings.h"

class SettingsUI
{
	char shortcut[64]{};
	int cofferValue = settings.settings.cofferValue;
	bool initialized = false;
	
public:
	SettingsUI() = default;

	void draw();
};

extern SettingsUI settingsUI;
