#include "KillproofUI.h"

#include <mutex>

#include "global.h"
#include "Player.h"
#include "Settings.h"

#define windowWidth 800
#define windowsHeight 650

void KillproofUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	ImGui::Begin(title, p_open, flags);

	// lock the mutexes, before we access sensible data
	std::scoped_lock lock(trackedPlayersMutex, cachedPlayersMutex);

	Settings& settings = Settings::instance();

	if (ImGui::BeginTable("kp.me", static_cast<int>(Killproof::FINAL_ENTRY) + 1,
	                      ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable)) {
		// Header
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder, 0, static_cast<ImU32>(Killproof::FINAL_ENTRY) + 1);
		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			Killproof kp = static_cast<Killproof>(i);
			int columnFlags = 0;

			if (defaultHidden(kp)) {
				columnFlags |= ImGuiTableColumnFlags_DefaultHide;
			}

			ImGui::TableSetupColumn(toString(kp), columnFlags, 0.f, static_cast<ImU32>(kp));
		}
		ImGui::TableHeadersRow();

		if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs()) {
			// Sort our data if sort specs have been changed!
			if (sorts_specs->SpecsDirty)
				needSort = true;
			
			bool expected = true;
			if (needSort.compare_exchange_strong(expected, false)) {
				const bool descend = sorts_specs->Specs->SortDirection == 2;

				if (sorts_specs->Specs->ColumnUserID == static_cast<ImGuiID>(Killproof::FINAL_ENTRY) + 1) {
					std::sort(trackedPlayers.begin(), trackedPlayers.end(), [descend](std::string playerAName, std::string playerBName) {
						std::transform(playerAName.begin(), playerAName.end(), playerAName.begin(),[](unsigned char c) { return std::tolower(c); });
						std::transform(playerBName.begin(), playerBName.end(), playerBName.begin(),[](unsigned char c) { return std::tolower(c); });
						if (descend) {
							return playerAName < playerBName;
						} else {
							return playerAName > playerBName;
						}
					});
				} else {
					std::sort(trackedPlayers.begin(), trackedPlayers.end(), [sorts_specs, descend](std::string playerAName, std::string playerBName) {
						// get player object of name
						const Player& playerA = cachedPlayers.at(playerAName);
						const Player& playerB = cachedPlayers.at(playerBName);

						const amountVal amountA = playerA.killproofs.getAmountFromEnum(static_cast<const Killproof>(sorts_specs->Specs->ColumnUserID));
						const amountVal amountB = playerB.killproofs.getAmountFromEnum(static_cast<const Killproof>(sorts_specs->Specs->ColumnUserID));

						if (descend) {
							return amountA < amountB;
						} else {
							return amountA > amountB;
						}
					});
				}
				sorts_specs->SpecsDirty = false;
			}
		}

		// List of all players
		for (const std::string& trackedPlayer : trackedPlayers) {
			const Player& player = cachedPlayers.at(trackedPlayer);

			// hide player they have data, when setting is active
			if (!(settings.getHidePrivateAccount() && player.noDataAvailable)) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("%s - %s", player.username.c_str(), player.characterName.c_str());

				for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
					ImGui::TableNextColumn();
					const amountVal amount = player.killproofs.getAmountFromEnum(static_cast<Killproof>(i));
					if (amount == -1 || player.noDataAvailable) {
						ImGui::Text("?");
					} else {
						ImGui::Text("%i", amount);
					}
				}
			}
		}

		ImGui::EndTable();
	}

	ImGui::End();
}
