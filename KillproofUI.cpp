#include "KillproofUI.h"

#include <mutex>
#include <set>

#include "global.h"
#include "Player.h"
#include "Settings.h"

#define windowWidth 800
#define windowsHeight 650
#define leftItemWidth  100

void KillproofUI::drawSingleKP(const char* name, amountVal amount, Settings& settings) {
	if (amount == -1) {
		if (!settings.getHidePrivateData()) {
			ImGui::Text(name);
			ImGui::SameLine(leftItemWidth);
			ImGui::Text("data private");
		}
	}
	else {
		ImGui::Text(name);
		ImGui::SameLine(leftItemWidth);
		ImGui::Text("%i", amount);
	}
}

void KillproofUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	ImGui::Begin(title, p_open, flags);

	// ImGui::SetNextTreeNodeOpen(true);
	// TreeNode with the player name
	std::scoped_lock lock(trackedPlayersMutex, cachedPlayersMutex);
	for (const std::string& trackedPlayer : trackedPlayers) {
		const Player& player = cachedPlayers.at(trackedPlayer);
		Settings& settings = Settings::instance();
		if (!(settings.getHidePrivateAccount() && player.noDataAvailable)) {
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
							drawSingleKP(toString(active.first), amount, settings);
						}
					}
				}

				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}
