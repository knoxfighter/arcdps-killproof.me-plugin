#include "KillproofUI.h"

#include <mutex>

#include "global.h"
#include "Player.h"
#include "Settings.h"

#define windowWidth 800
#define windowsHeight 650

void KillproofUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	ImGui::Begin(title, p_open, flags);

	// lock the mutexes, before we access sensible data
	std::scoped_lock lock(trackedPlayersMutex, cachedPlayersMutex);

	Settings& settings = Settings::instance();

	const int columnCount = static_cast<int>(Killproof::FINAL_ENTRY) + 2;

	if (ImGui::BeginTable("kp.me", columnCount,
	                      ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable | ImGuiTableFlags_RowBg)) {
		ImU32 accountNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 1;
		ImU32 characterNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 2;

		// Header
		ImGui::TableSetupColumn("Accountname", ImGuiTableColumnFlags_NoReorder, 0, accountNameId);
		ImGui::TableSetupColumn("Charactername", ImGuiTableColumnFlags_NoReorder, 0, characterNameId);

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

				if (sorts_specs->Specs->ColumnUserID == accountNameId) {
					// sort by account name. Account name is the value we used in trackedPlayers, so nothing more to do
					std::sort(trackedPlayers.begin(), trackedPlayers.end(), [descend](std::string playerAName, std::string playerBName) {
						std::transform(playerAName.begin(), playerAName.end(), playerAName.begin(), [](unsigned char c) { return std::tolower(c); });
						std::transform(playerBName.begin(), playerBName.end(), playerBName.begin(), [](unsigned char c) { return std::tolower(c); });

						if (descend) {
							return playerAName < playerBName;
						} else {
							return playerAName > playerBName;
						}
					});
				} else if (sorts_specs->Specs->ColumnUserID == characterNameId) {
					// sort by character name
					std::sort(trackedPlayers.begin(), trackedPlayers.end(), [descend](std::string playerAName, std::string playerBName) {
						std::string playerAChar = cachedPlayers.at(playerAName).characterName;
						std::string playerBChar = cachedPlayers.at(playerBName).characterName;

						std::transform(playerAChar.begin(), playerAChar.end(), playerAChar.begin(), [](unsigned char c) { return std::tolower(c); });
						std::transform(playerBChar.begin(), playerBChar.end(), playerBChar.begin(), [](unsigned char c) { return std::tolower(c); });

						if (descend) {
							return playerAChar < playerBChar;
						} else {
							return playerAChar > playerBChar;
						}
					});
				} else {
					// sort by any amount of KP
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

				// username
				ImGui::TableNextColumn();
				ImGui::Text(player.username.c_str());

				// charactername
				ImGui::TableNextColumn();
				ImGui::Text(player.characterName.c_str());

				for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
					ImGui::TableNextColumn();
					const amountVal amount = player.killproofs.getAmountFromEnum(static_cast<Killproof>(i));
					if (amount == -1 || player.noDataAvailable) {
						ImGui::Text("%s", settings.getBlockedDataText().c_str());
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
