#pragma once

#include <atomic>

#include "imgui/imgui.h"

class KillproofUI
{
public:
	std::atomic_bool needSort = false;
	
	void draw(bool* p_open, ImGuiWindowFlags flags);
	void AlignedTextColumn(const char* text, ...) const;
	void TableHeader(const char* label, bool show_text);
	bool SpinnerAligned(const char* label, float radius, float thickness, const ImU32& color);
	bool Spinner(const char* label, float radius, float thickness, const ImU32& color);

private:
	static void openInBrowser(const char* username);

	char userAddBuf[1024]{};
};


