#pragma once

#include <cstdint>
#include <map>
#include <set>

#include "Player.h"
#include "imgui/imgui.h"

struct KillproofUI
{
private:
	void drawSingleKP(const char* name, uint16_t amount);

public:
	void draw(const char* title, bool* p_open, ImGuiWindowFlags flags, const std::map<std::string, Player>& cachedPlayers, const std::set<std::string>& trackedPlayers);
};


