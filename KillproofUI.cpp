#include "KillproofUI.h"

#include <mutex>
#include <set>

#include "global.h"
#include "Player.h"
#include "Settings.h"

#define windowWidth 800
#define windowsHeight 650
#define leftItemWidth  100

void KillproofUI::drawSingleKP(const char* name, amountVal amount) {
	ImGui::Text(name);
	ImGui::SameLine(leftItemWidth);
	if (amount == -1) {
		ImGui::Text("data private");
	}
	else {
		ImGui::Text("%i", amount);
	}
}

void KillproofUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowsHeight), ImGuiSetCond_FirstUseEver);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(150, 50));
	ImGui::Begin(title, p_open, flags);

	// ImGui::SetNextTreeNodeOpen(true);
	// TreeNode with the player name
	std::lock_guard<std::mutex> playerGuard(trackedPlayersMutex);
	std::lock_guard<std::mutex> cacheGuard(cachedPlayersMutex);
	for (const std::string& trackedPlayer : trackedPlayers) {
		const Player& player = cachedPlayers.at(trackedPlayer);
		char buf[2048];
		snprintf(buf, 2048, "%s - %s", player.username.c_str(), player.characterName.c_str());
		if (ImGui::TreeNode(buf)) {
			if (player.noDataAvailable) {
				ImGui::Text("no data available");
			}
			else {
				Settings& settings = Settings::instance();
				kpActiveMap& actives = settings.getActive();
				for (auto& active : actives) {
					if (active.second) {
						amountVal amount = player.killproofs.getAmountFromEnum(active.first);
						drawSingleKP(toString(active.first), amount);
					}
				}
			}

			ImGui::TreePop();
		}
	}

	ImGui::End();
	ImGui::PopStyleVar(1);
}
