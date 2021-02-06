#pragma once

#include <atomic>

#include "imgui/imgui.h"

struct KillproofUI
{
	std::atomic_bool needSort = false;
	
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);
};


