#include "KillproofUI.h"

#include <mutex>
#include <Windows.h>

#include "global.h"
#include "Player.h"
#include "Settings.h"

#define windowWidth 800
#define windowsHeight 650

void KillproofUI::openInBrowser(const char* username) {
	char buf[128];
	snprintf(buf, 128, "https://killproof.me/proof/%s", username);
	ShellExecuteA(nullptr, nullptr, buf, nullptr, nullptr, SW_SHOW);
}

void KillproofUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	ImGui::Begin(title, p_open, flags);

	// lock the mutexes, before we access sensible data
	std::scoped_lock lock(trackedPlayersMutex, cachedPlayersMutex);

	Settings& settings = Settings::instance();

	/**
	 * ERROR MESSAGES
	 */
	for (std::string trackedPlayer : trackedPlayers) {
		const Player& player = cachedPlayers.at(trackedPlayer);
		if (player.status == LoadingStatus::KpMeError) {
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", player.errorMessage.c_str());
		}
	}

	/**
	 * Controls
	 */
	bool addPlayer = false;
	if (ImGui::InputText("##useradd", userAddBuf, sizeof userAddBuf, ImGuiInputTextFlags_EnterReturnsTrue)) {
		addPlayer = true;
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Accountname to add to the list (use account names, input without '.' will be ignored)");
	ImGui::SameLine();
	if (ImGui::Button("Add")) {
		addPlayer = true;
	}

	if (addPlayer) {
		std::string username(userAddBuf);

		// only add users with a '.' in it
		if (!username.find('.')) {
			trackedPlayers.emplace_back(username);

			const auto& tryEmplace = cachedPlayers.try_emplace(username, username, "");
			loadKillproofsSizeChecked(tryEmplace.first->second);
			userAddBuf[0] = '\0';
		}
	}
	
	/**
	 * TABLE
	 */
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
			if (!(settings.getHidePrivateAccount() && player.status == LoadingStatus::NoDataAvailable)) {
				ImGui::TableNextRow();

				// username
				ImGui::TableNextColumn();
				ImGui::Text(player.username.c_str());
				if (!(player.status == LoadingStatus::NoDataAvailable) && ImGui::IsItemClicked()) {
					// Open users kp.me in the browser
					openInBrowser(player.username.c_str());
				}

				// charactername
				ImGui::TableNextColumn();
				ImGui::Text(player.characterName.c_str());
				if (ImGui::IsItemClicked()) {
					// Open users kp.me in the browser
					openInBrowser(player.username.c_str());
				}

				for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
					ImGui::TableNextColumn();
					const amountVal amount = player.killproofs.getAmountFromEnum(static_cast<Killproof>(i));
					if (amount == -1 || player.status != LoadingStatus::Loaded) {
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
