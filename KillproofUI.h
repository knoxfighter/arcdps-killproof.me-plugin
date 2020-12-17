#pragma once

#include <cstdint>

#include "Killproofs.h"
#include "imgui/imgui.h"

struct KillproofUI
{
private:
	void drawSingleKP(const char* name, amountVal amount);

public:
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};


