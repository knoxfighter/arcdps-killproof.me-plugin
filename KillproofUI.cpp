#include "KillproofUI.h"

#include <mutex>
#include <Windows.h>
#include <future>

#include "global.h"
#include "Player.h"
#include "Settings.h"
#include "extension//Icon.h"
#include "Lang.h"
#include "imgui/imgui_internal.h"
#include "extension/Widgets.h"
#include "WindowSettingsUI.h"

void KillproofUI::openInBrowser(const char* username) {
	const auto& string = std::format("https://killproof.me/proof/{}", username);
	std::thread([string] {
		ShellExecuteA(nullptr, nullptr, string.c_str(), nullptr, nullptr, SW_SHOW);
	}).detach();
}

void KillproofUI::draw(bool* p_open, ImGuiWindowFlags flags) {
	// ImGui::SetNextWindowSizeConstraints(ImVec2(150, 50), ImVec2(windowWidth, windowsHeight));
	std::string title = lang.translate(LangKey::KpWindowName);
	title.append("##Killproof.me");

	flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	if (!settings.getShowHeader()) {
		flags |= ImGuiWindowFlags_NoTitleBar;
	}

	if (settings.getPosition() != Position::Manual) {
		flags |= ImGuiWindowFlags_NoMove;
	}

	ImGui::Begin(title.c_str(), p_open, flags);

	/**
	 * Settings UI
	 */
	ImGuiWindow* currentWindow = ImGui::GetCurrentWindow();
	if (ImGuiEx::BeginPopupContextWindow(nullptr, 1, ImGuiHoveredFlags_ChildWindows)) {
		windowSettingsUI.draw(table, currentWindow);

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
	 * Unofficial Extras message
	 */
	if (!extrasLoaded && !settings.getHideExtrasMessage()) {
		ImGui::TextUnformatted(lang.translate(LangKey::UnofficialExtrasNotInstalled).c_str());

		ImGui::SameLine();
		if (ImGui::Button(lang.translate(LangKey::UpdateOpenPage).c_str())) {
			std::thread([] {
				ShellExecuteA(nullptr, nullptr, "https://github.com/Krappa322/arcdps_unofficial_extras_releases/releases/latest", nullptr, nullptr, SW_SHOW);
			}).detach();
		}

		ImGui::SameLine();
		if (ImGui::Button("X")) {
			extrasLoaded = true;
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
				const auto& existingPlayer = std::ranges::find_if(cachedPlayers, [&username](const auto& elem) -> bool {
					return elem.first == username || elem.second.characterName == username || elem.second.killproofId == username;
				});

				if (existingPlayer == cachedPlayers.end()) {
					// add new player
					trackedPlayers.emplace_back(username);

					const auto& tryEmplace = cachedPlayers.try_emplace(username, username, AddedBy::Manually);
					// This should always be `true`
					if (tryEmplace.second) {
						loadKillproofs(tryEmplace.first->second);
					}
				} else {
					// player already exists
					// update username to actual accountname
					username = existingPlayer->first;
					
					// check of player is already tracked
					if (std::ranges::find(trackedPlayers, username) == trackedPlayers.end()) {
						// not yet tracked, add to tracking and update
						trackedPlayers.emplace_back(username);

						// set to Manually added
						existingPlayer->second.addedBy = AddedBy::Manually;
						existingPlayer->second.resetJoinedTime();
						loadKillproofs(existingPlayer->second);
					} else {
						// user already exists and user is already tracked -> Try to load killproofs to override sizeCheck
						loadKillproofs(existingPlayer->second);
					}
				}
				userAddBuf[0] = '\0';
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(lang.translate(LangKey::ClearText).c_str())) {
			trackedPlayers = instancePlayers;
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
					// create string to copy
					std::string str;
					str.append("Killproof.me: ");
					str.append(player.killproofId);

					// copy ID to clipboard
					//put your text in source
					if (OpenClipboard(NULL)) {
						HGLOBAL clipbuffer;
						char* buffer;
						EmptyClipboard();
						clipbuffer = GlobalAlloc(GMEM_DDESHARE, str.size() + 1);
						buffer = (char*)GlobalLock(clipbuffer);
						memset(buffer, 0, str.size() + 1);
						str.copy(buffer, str.size());
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
	Alignment headerAlignment = settings.getHeaderAlignment();
	const int columnCount = static_cast<int>(Killproof::FINAL_ENTRY) + 4;

	if (ImGui::BeginTable("kp.me", columnCount,
						  ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable |
						  ImGuiTableFlags_Reorderable | ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX)) {
		table = GImGui->CurrentTable;
		ImU32 accountNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 1;
		ImU32 characterNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 2;
		ImU32 killproofId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 3;
		ImU32 joinTimeId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 4;

		std::string accountName = lang.translate(LangKey::Accountname);
		std::string charName = lang.translate(LangKey::Charactername);
		std::string killproofName = lang.translate(LangKey::KillproodId);

		/**
		 * HEADER
		 */
		ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_PreferSortDescending, 0, joinTimeId);
		ImGui::TableSetupColumn(accountName.c_str(), ImGuiTableColumnFlags_PreferSortDescending, 0, accountNameId);
		ImGui::TableSetupColumn(charName.c_str(), ImGuiTableColumnFlags_PreferSortDescending, 0, characterNameId);
		ImGui::TableSetupColumn(killproofName.c_str(), ImGuiTableColumnFlags_PreferSortDescending, 0, killproofId);

		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			Killproof kp = static_cast<Killproof>(i);
			int columnFlags = ImGuiTableColumnFlags_PreferSortDescending;

			if (defaultHidden(kp)) {
				columnFlags |= ImGuiTableColumnFlags_DefaultHide;
			}

			ImGui::TableSetupColumn(toString(kp).c_str(), columnFlags, 0.f, static_cast<ImU32>(kp));
		}

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

		// join time
		if (ImGui::TableNextColumn())
			ImGuiEx::TableHeader("#", true, nullptr);

		// accountname header
		if (ImGui::TableNextColumn())
			ImGuiEx::TableHeader(accountName.c_str(), true, nullptr);

		// charname header
		if (ImGui::TableNextColumn())
			ImGuiEx::TableHeader(charName.c_str(), true, nullptr);

		// killproof ID
		if (ImGui::TableNextColumn()) {
			ImGuiEx::TableHeader(killproofName.c_str(), true, nullptr);
		}

		// header for killproofs
		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			if (ImGui::TableNextColumn()) {
				Killproof kp = static_cast<Killproof>(i);
				std::string columnName = toString(kp);
				if (settings.getShowHeaderText()) {
					ImGuiEx::TableHeader(columnName.c_str(), true, nullptr, headerAlignment);
				} else {
					ImGuiEx::TableHeader(columnName.c_str(), false, iconLoader.getTexture(icons.at(kp)), headerAlignment);
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

				if (sorts_specs->Specs->ColumnUserID == joinTimeId) {
					std::ranges::sort(trackedPlayers, [descend](const std::string& playerAName, const std::string& playerBName) -> bool {
						const SYSTEMTIME& joinedTimeA = cachedPlayers.at(playerAName).joinedTime;
						const SYSTEMTIME& joinedTimeB = cachedPlayers.at(playerBName).joinedTime;

						if (descend) {
							return joinedTimeA.wHour < joinedTimeB.wHour || (joinedTimeA.wHour == joinedTimeB.wHour && (joinedTimeA.wMinute < joinedTimeB.
								wMinute || (joinedTimeA.wMinute == joinedTimeB.wMinute && joinedTimeA.wSecond < joinedTimeB.wSecond)));
						} else {
							return joinedTimeA.wHour > joinedTimeB.wHour || (joinedTimeA.wHour == joinedTimeB.wHour && (joinedTimeA.wMinute > joinedTimeB.
								wMinute || (joinedTimeA.wMinute == joinedTimeB.wMinute && joinedTimeA.wSecond > joinedTimeB.wSecond)));
						}
					});
				} else if (sorts_specs->Specs->ColumnUserID == accountNameId) {
					// sort by account name. Account name is the value we used in trackedPlayers, so nothing more to do
					std::ranges::sort(trackedPlayers, [descend](std::string playerAName, std::string playerBName) {
						std::ranges::transform(playerAName, playerAName.begin(), [](unsigned char c) { return std::tolower(c); });
						std::ranges::transform(playerBName, playerBName.begin(), [](unsigned char c) { return std::tolower(c); });

						if (descend) {
							return playerAName < playerBName;
						} else {
							return playerAName > playerBName;
						}
					});
				} else if (sorts_specs->Specs->ColumnUserID == characterNameId) {
					// sort by character name
					std::ranges::sort(trackedPlayers, [descend](const std::string& playerAName, const std::string& playerBName) {
						std::string playerAChar = cachedPlayers.at(playerAName).characterName;
						std::string playerBChar = cachedPlayers.at(playerBName).characterName;

						std::ranges::transform(playerAChar, playerAChar.begin(), [](unsigned char c) { return std::tolower(c); });
						std::ranges::transform(playerBChar, playerBChar.begin(), [](unsigned char c) { return std::tolower(c); });

						if (descend) {
							return playerAChar < playerBChar;
						} else {
							return playerAChar > playerBChar;
						}
					});
				} else {
					// sort by any amount of KP
					std::ranges::sort(trackedPlayers, [sorts_specs, descend](const std::string& playerAName, const std::string& playerBName) {
						// get player object of name
						const Player& playerA = cachedPlayers.at(playerAName);
						const Player& playerB = cachedPlayers.at(playerBName);

						const Killproof kp = static_cast<const Killproof>(sorts_specs->Specs->ColumnUserID);
						amountVal amountA = playerA.getKpOverall(kp);
						amountVal amountB = playerB.getKpOverall(kp);

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

			// hide player without data, when setting is active
			if (!(settings.getHidePrivateAccount() && player.status == LoadingStatus::NoDataAvailable)) {
				bool open = drawRow(alignment, &player.joinedTime, player.username.c_str(), player.characterName.c_str(), player.killproofId.c_str(),
									player.status,
									[&player](const Killproof& kp) { return player.getKillproofs(kp); },
									[&player](const Killproof& kp) { return player.getCoffers(kp); },
									[&player](const Killproof& kp) { return player.getKpOverall(kp); },
									player.linkedTotalKillproofs.has_value(), player.commander);
				if (open) {
					for (std::string linkedAccount : player.linkedAccounts) {
						Player& linkedPlayer = cachedPlayers.at(linkedAccount);
						drawRow(alignment, nullptr, linkedPlayer.username.c_str(), linkedPlayer.characterName.c_str(), linkedPlayer.killproofId.c_str(),
								LoadingStatus::Loaded,
								[&linkedPlayer](const Killproof& kp) { return linkedPlayer.getKillproofs(kp); },
								[&linkedPlayer](const Killproof& kp) { return linkedPlayer.getCoffers(kp); },
								[&linkedPlayer](const Killproof& kp) { return linkedPlayer.getKpOverall(kp); },
								false, false);
					}
					drawRow(alignment, nullptr, lang.translate(LangKey::Overall).c_str(), "--->", "", player.status,
							[&player](const Killproof& kp) { return player.getKillproofsTotal(kp); },
							[&player](const Killproof& kp) { return player.getCoffersTotal(kp); },
							[&player](const Killproof& kp) { return player.getKpOverallTotal(kp); },
							false, false);

					ImGui::TreePop();
				}
			}
		}

		ImGui::EndTable();
	}

	/**
	 * Reposition Window
	 */
	ImGuiEx::WindowReposition(settings.getPosition(), settings.getCornerVector(), settings.getCornerPosition(), settings.getFromWindowID(),
							  settings.getAnchorPanelCornerPosition(), settings.getSelfPanelCornerPosition());

	ImGui::End();
}

void KillproofUI::drawTextRow(bool* open, const char* text, const char* usernameLink, const std::atomic<LoadingStatus>& status, bool treeNode) {
	if (treeNode) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;
		if (settings.getShowOverallByDefault()) {
			treeNodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
		}

		*open = ImGui::TreeNodeEx(text, treeNodeFlags);
		ImGui::PopStyleVar();
	} else {
		ImGui::TextUnformatted(text);
		if (status == LoadingStatus::Loaded && ImGui::IsItemClicked()) {
			// Open users kp.me in the browser
			openInBrowser(usernameLink);
		}
	}
}

bool KillproofUI::drawRow(const Alignment& alignment, const SYSTEMTIME* joinTime, const char* username, const char* characterName, const char* killproofId,
						  const std::atomic<LoadingStatus>& status,
						  kpFunction killproofsFun, kpFunction coffersFun, kpFunction kpOverallFun, bool treeNode, bool isCommander) {
	ImGui::TableNextRow();

	bool open = false;

	// find first column that is visible
	ImGuiTableColumnIdx first;
	for (int i = 0; i <= table->ColumnsCount; ++i) {
		if (table->EnabledMaskByDisplayOrder & ((ImU64)1 << i)) {
			first = table->DisplayOrderToIndex[i];
			break;
		}
	}

	// #
	if (ImGui::TableNextColumn() && joinTime) {
		drawTextRow(&open, std::format("{:02d}:{:02d}:{:02d}##{}", joinTime->wHour, joinTime->wMinute, joinTime->wSecond, username).c_str(), username, status,
					first == ImGui::TableGetColumnIndex() && treeNode);
	}

	// username
	if (ImGui::TableNextColumn()) {
		// TODO: implement in first column only
		// if (isCommander && settings.getShowCommander()) {
		// 	auto* icon = iconLoader.getTexture(ID_Commander_White);
		// 	if (icon) {
		// 		float size = ImGui::GetFontSize();
		// 		ImGui::Image(icon, ImVec2(size, size));
		// 		ImGui::SameLine();
		// 	}
		// }
		drawTextRow(&open, username, username, status, first == ImGui::TableGetColumnIndex() && treeNode);
	}

	// charactername
	if (ImGui::TableNextColumn()) {
		drawTextRow(&open, characterName, username, status, first == ImGui::TableGetColumnIndex() && treeNode);
	}

	// killproofID
	if (ImGui::TableNextColumn()) {
		drawTextRow(&open, killproofId, username, status, first == ImGui::TableGetColumnIndex() && treeNode);
	}

	for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
		if (ImGui::TableNextColumn()) {
			Killproof kp = static_cast<Killproof>(i);
			amountVal totalAmount = kpOverallFun(kp);

			if (status == LoadingStatus::LoadingById || status == LoadingStatus::LoadingByChar) {
				ImGuiEx::SpinnerAligned("loadingSpinner", ImGui::GetTextLineHeight() / 4.f, 1.f, ImGui::GetColorU32(ImGuiCol_Text), settings.getAlignment());
			} else if (totalAmount == -1 || status != LoadingStatus::Loaded) {
				ImGuiEx::AlignedTextColumn(alignment, "%s", settings.getBlockedDataText().c_str());
			} else {
				ImGuiEx::AlignedTextColumn(alignment, "%i", totalAmount);

				if (ImGui::IsItemHovered()) {
					ImGui::BeginTooltip();
					std::string kpText = std::format("{}: {}", lang.translate(LangKey::Killproofs), killproofsFun(kp));
					ImGui::TextUnformatted(kpText.c_str());
					std::string cofferText = std::format("{}: {}", lang.translate(LangKey::Coffers), coffersFun(kp));
					ImGui::TextUnformatted(cofferText.c_str());
					ImGui::EndTooltip();
				}
			}
		}
	}

	return open;
}
