#include "KillproofUI.h"

#include <mutex>
#include <Windows.h>

#include "global.h"
#include "Player.h"
#include "Settings.h"
#include "extension//Icon.h"
#include "Lang.h"
#include "imgui/imgui_internal.h"
#include "extension/Widgets.h"
#include "WindowSettingsUI.h"

void KillproofUI::openInBrowser(const char* username) {
	char buf[128];
	snprintf(buf, 128, "https://killproof.me/proof/%s", username);
	ShellExecuteA(nullptr, nullptr, buf, nullptr, nullptr, SW_SHOW);
}

void KillproofUI::draw(bool* p_open, ImGuiWindowFlags flags) {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	std::string title = lang.translate(LangKey::KpWindowName);
	title.append("##Killproof.me");

	flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	ImGui::Begin(title.c_str(), p_open, flags);

	/**
	 * Settings UI
	 */
	if (ImGuiEx::BeginPopupContextWindow(nullptr, 1, ImGuiHoveredFlags_ChildWindows)) {
		windowSettingsUI.draw(table);
	
		ImGui::EndPopup();
	}

	// lock the mutexes, before we access sensible data
	std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);


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
	if (!settings.getHideControls()) {
		bool addPlayer = false;
		if (ImGui::InputText("##useradd", userAddBuf, sizeof userAddBuf, ImGuiInputTextFlags_EnterReturnsTrue)) {
			addPlayer = true;
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(lang.translate(LangKey::AddPlayerTooltip).c_str());
		ImGui::SameLine();
		if (ImGui::Button(lang.translate(LangKey::AddPlayerText).c_str())) {
			addPlayer = true;
		}

		if (addPlayer) {
			std::string username(userAddBuf);

			// only run when username is not empty
			if (!username.empty()) {
				// only add to tracking, if not already there
				if (std::find(trackedPlayers.begin(), trackedPlayers.end(), username) == trackedPlayers.end()) {
					trackedPlayers.emplace_back(username);

					const auto& tryEmplace = cachedPlayers.try_emplace(username, username, "", true);
					if (tryEmplace.second) {
						loadKillproofs(tryEmplace.first->second);
					}
				}
				userAddBuf[0] = '\0';
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(lang.translate(LangKey::ClearText).c_str())) {
			const auto end = std::remove_if(trackedPlayers.begin(), trackedPlayers.end(), [](const std::string& playerName) {
				const auto& player = cachedPlayers.find(playerName);
				if (player == cachedPlayers.end()) {
					return false;
				}
				return player->second.manuallyAdded;
			});
			trackedPlayers.erase(end, trackedPlayers.end());
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(lang.translate(LangKey::ClearTooltip).c_str());
		}

		// get own player
		const auto& playerIt = cachedPlayers.find(selfAccountName);
		if (playerIt != cachedPlayers.end()) {
			const Player& player = playerIt->second;
			if (player.status == LoadingStatus::Loaded) {
				ImGui::SameLine();

				if (ImGui::Button(lang.translate(LangKey::CopyKpIdText).c_str())) {
					// copy ID to clipboard
					//put your text in source
					if (OpenClipboard(NULL)) {
						HGLOBAL clipbuffer;
						char* buffer;
						EmptyClipboard();
						clipbuffer = GlobalAlloc(GMEM_DDESHARE, player.killproofId.size() + 1);
						buffer = (char*)GlobalLock(clipbuffer);
						memset(buffer, 0, player.killproofId.size() + 1);
						player.killproofId.copy(buffer, player.killproofId.size());
						GlobalUnlock(clipbuffer);
						SetClipboardData(CF_TEXT, clipbuffer);
						CloseClipboard();
					}
				}
			}
		}
	}

	/**
	* TABLE
	*/
	Alignment alignment = settings.getAlignment();
	const int columnCount = static_cast<int>(Killproof::FINAL_ENTRY) + 2;

	if (ImGui::BeginTable("kp.me", columnCount,
	                      ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable |
	                      ImGuiTableFlags_Reorderable | ImGuiTableFlags_RowBg)) {
		table = GImGui->CurrentTable;
		ImU32 accountNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 1;
		ImU32 characterNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 2;

		std::string accountName = lang.translate(LangKey::Accountname);
		std::string charName = lang.translate(LangKey::Charactername);

		/**
		 * HEADER
		 */
		ImGui::TableSetupColumn(accountName.c_str(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_PreferSortDescending, 0, accountNameId);
		ImGui::TableSetupColumn(charName.c_str(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_PreferSortDescending, 0, characterNameId);

		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			Killproof kp = static_cast<Killproof>(i);
			int columnFlags = ImGuiTableColumnFlags_PreferSortDescending;

			if (defaultHidden(kp)) {
				columnFlags |= ImGuiTableColumnFlags_DefaultHide;
			}

			ImGui::TableSetupColumn(toString(kp).c_str(), columnFlags, 0.f, static_cast<ImU32>(kp));
		}

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

		// accountname header
		if (ImGui::TableNextColumn())
			ImGuiEx::TableHeader(accountName.c_str(), true, nullptr);

		// charname header
		if (ImGui::TableNextColumn())
			ImGuiEx::TableHeader(charName.c_str(), true, nullptr);

		// header for killproofs
		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			if (ImGui::TableNextColumn()) {
				Killproof kp = static_cast<Killproof>(i);
				std::string columnName = toString(kp);
				if (settings.getShowHeaderText()) {
					ImGuiEx::TableHeader(columnName.c_str(), true, nullptr, alignment);
				} else {
					ImGuiEx::TableHeader(columnName.c_str(), false, icons.at(kp).texture, alignment);
				}
			}
		}

		/**
		 * SORTING
		 */
		if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs()) {
			// Sort our data if sort specs have been changed!
			if (sorts_specs->SpecsDirty)
				needSort = true;

			bool expected = true;
			if (needSort.compare_exchange_strong(expected, false)) {
				const bool descend = sorts_specs->Specs->SortDirection == ImGuiSortDirection_Descending;

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

						// descending: the more the higher up it gets
						if (descend) {
							return amountA > amountB;
						} else {
							return amountA < amountB;
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
				if (ImGui::TableNextColumn()) {
					ImGui::Text(player.username.c_str());
					if (player.status == LoadingStatus::Loaded && ImGui::IsItemClicked()) {
						// Open users kp.me in the browser
						openInBrowser(player.username.c_str());
					}
				}

				// charactername
				if (ImGui::TableNextColumn()) {
					ImGui::Text(player.characterName.c_str());
					if (player.status == LoadingStatus::Loaded && ImGui::IsItemClicked()) {
						// Open users kp.me in the browser
						openInBrowser(player.username.c_str());
					}
				}

				for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
					if (ImGui::TableNextColumn()) {
						const amountVal amount = player.killproofs.getAmountFromEnum(static_cast<Killproof>(i));
						if (player.status == LoadingStatus::LoadingById || player.status == LoadingStatus::LoadingByChar) {
							ImGuiEx::SpinnerAligned("loadingSpinner", ImGui::GetTextLineHeight() / 4.f, 1.f, ImGui::GetColorU32(ImGuiCol_Text), settings.getAlignment());
						} else if (amount == -1 || player.status != LoadingStatus::Loaded) {
							ImGuiEx::AlignedTextColumn(alignment, "%s", settings.getBlockedDataText().c_str());
						} else {
							ImGuiEx::AlignedTextColumn(alignment, "%i", amount);
						}
					}
				}
			}
		}

		ImGui::EndTable();
	}

	ImGui::End();
}
