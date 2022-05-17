#pragma once

#include "Settings.h"

class SettingsUI : public Singleton<SettingsUI> {
public:
	SettingsUI() = default;

	void Draw();
};
