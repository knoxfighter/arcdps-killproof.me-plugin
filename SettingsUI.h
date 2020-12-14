#pragma once

#include "imgui/imgui.h"

class SettingsUI
{
public:
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};

