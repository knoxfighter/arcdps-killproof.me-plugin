#pragma once

#include <atomic>

#include "imgui/imgui.h"

class KillproofUI
{
public:
	std::atomic_bool needSort = false;
	
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags);

private:
	static void openInBrowser(const char* username);

	char userAddBuf[1024]{};
};


