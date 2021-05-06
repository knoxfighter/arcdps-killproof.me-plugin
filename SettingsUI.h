#pragma once

class SettingsUI
{
	char shortcut[64]{};
	char shortCutRealName[32]{};
	
public:
	SettingsUI();

	void draw();
};

extern SettingsUI settingsUI;
