#pragma once

#include <cstdint>

#include "Killproofs.h"
#include "Settings.h"
#include "imgui/imgui.h"

struct KillproofUI
{
private:
	void drawSingleKP(const char* name, int32_t amount, Settings& settings);

public:
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};


