#pragma once

#include <cstdint>

#include "imgui/imgui.h"

struct KillproofUI
{
private:
	void drawSingleKP(const char* name, uint16_t amount);

public:
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};


