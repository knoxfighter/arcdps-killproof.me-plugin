#include "KillproofUI.h"

#include "global.h"
#include "KillproofUIPositioningComponent.h"
#include "KillproofUIKeyBindComponent.h"
#include "Lang.h"
#include "Player.h"
#include "resource.h"
#include "Settings.h"

#include "extension/Icon.h"
#include "extension/imgui_stdlib.h"
#include "extension/Widgets.h"

#include <future>
#include <mutex>
#include <Windows.h>

using std::string_literals::operator ""s;

void KillproofUI::openInBrowser(const char* username) {
	const auto& string = std::format("https://killproof.me/proof/{}", username);
	std::thread([string] {
		ShellExecuteA(nullptr, nullptr, string.c_str(), nullptr, nullptr, SW_SHOW);
	}).detach();
}

KillproofUI::KillproofUI() {
	CreateComponent<KillproofUIPositioningComponent>();
	CreateComponent<KillproofUIKeyBindComponent>();
}

bool& KillproofUI::GetOpenVar() {
	return Settings::instance().settings.showKillproof;
}

void KillproofUI::SetMaxHeightCursorPos(float pNewCursorPos) {
	// Table border size is hardcoded within ImGui `TABLE_BORDER_SIZE = 1.0f;`

	// [ DEBUG ]
	// ImGuiWindow* subWindow = ImGui::GetCurrentWindow();
	// ImGui::GetForegroundDrawList(mThisWindow)->AddRect(subWindow->Pos, subWindow->Pos + subWindow->Size, 0xff00ff00);
	// ImVec2 imVec2 = ;
	// imVec2.y -= pNewCursorPos;
	// ImGui::GetForegroundDrawList(mThisWindow)->AddRect(subWindow->Pos, subWindow->Pos + ImGui::GetCursorPos(), 0xffffff00);

	mCurrentCursorPos = pNewCursorPos;
}

SizingPolicy& KillproofUI::getSizingPolicy() {
	return Settings::instance().settings.sizingPolicy;
}

bool& KillproofUI::getShowTitleBar() {
	return Settings::instance().settings.showHeader;
}

std::optional<std::string>& KillproofUI::getTitle() {
	return Settings::instance().settings.headerText;
}

const std::string& KillproofUI::getTitleDefault() {
	return lang.translate(LangKey::KpWindowName);
}

const std::string& KillproofUI::getWindowID() {
	return "Killproof.me"s;
}

std::optional<std::string>& KillproofUI::getAppearAsInOption() {
	return Settings::instance().settings.appearAsInOption;
}

const std::string& KillproofUI::getAppearAsInOptionDefault() {
	return lang.translate(LangKey::SubMenuKp);
}

bool& KillproofUI::getShowBackground() {
	return Settings::instance().settings.showBackground;
}

bool& KillproofUI::getShowScrollbar() {
	return Settings::instance().settings.showScrollbar;
}

std::optional<ImVec2>& KillproofUI::getPadding() {
	return Settings::instance().settings.windowPadding;
}

bool KillproofUI::getMaxHeightActive() {
	return Settings::instance().settings.maxDisplayed > 0;
}

void KillproofUI::DrawContextMenu() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

	if (ImGui::BeginMenu(lang.translate(LangKey::SettingsColumnSetup).c_str())) {
		ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

		// #
		ImGuiEx::MenuItemTableColumnVisibility(table, 0);
		// username
		ImGuiEx::MenuItemTableColumnVisibility(table, 1);
		// charname
		ImGuiEx::MenuItemTableColumnVisibility(table, 2);
		// id
		ImGuiEx::MenuItemTableColumnVisibility(table, 3);

		constexpr int beginCol = 4;


		// Raids
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsGroup).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::li) + beginCol);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ld) + beginCol);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::liLd) + beginCol);

			// W1
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW1Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::vg) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::gorse) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sabetha) + beginCol);

				ImGui::EndMenu();
			}

			// W2
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW2Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sloth) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::matthias) + beginCol);

				ImGui::EndMenu();
			}

			// W3
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW3Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::escort) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::kc) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::xera) + beginCol);

				ImGui::EndMenu();
			}

			// W4
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW4Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::cairn) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::mo) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::samarog) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::deimos) + beginCol);

				ImGui::EndMenu();
			}

			// W5
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW5Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::desmina) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::river) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::statues) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::dhuum) + beginCol);

				ImGui::EndMenu();
			}

			// W6
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW6Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ca) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::twins) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::qadim) + beginCol);

				ImGui::EndMenu();
			}

			// W7
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW7Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sabir) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::adina) + beginCol);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::qadim2) + beginCol);

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		// Fractals
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsFractalsGroup).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::uce) + beginCol);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ufe) + beginCol);

			ImGui::EndMenu();
		}

		// Strikes
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsStrikesGruop).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::boneskinnerVial) + beginCol);

			ImGui::EndMenu();
		}

		ImGui::PopItemFlag();

		ImGui::EndMenu();
	}

	ImGui::PopStyleVar();
}

void KillproofUI::DrawStyleSettingsSubMenu() {
	Settings& settings = Settings::instance();
	ImGui::Checkbox(lang.translate(LangKey::SettingsShowPrivateText).c_str(), &settings.settings.showPrivateAccounts);
	ImGui::Checkbox(lang.translate(LangKey::SettingsShowControls).c_str(), &settings.settings.showControls);
	ImGui::Checkbox(lang.translate(LangKey::SettingsShowLinkedByDefault).c_str(), &settings.settings.showLinkedByDefault);
	ImGui::Checkbox(lang.translate(LangKey::SettingsShowCommander).c_str(), &settings.settings.showCommander);

	// input for data private
	ImGui::PushItemWidth(50);
	ImGui::InputText(lang.translate(LangKey::SettingsBlockedText).c_str(), &settings.settings.blockedDataText);
	ImGui::PopItemWidth();

	ImGuiEx::EnumCombo(lang.translate(LangKey::Alignment).c_str(), settings.settings.alignment, Alignment::Unaligned);
	ImGuiEx::EnumCombo(lang.translate(LangKey::HeaderAlignment).c_str(), settings.settings.headerAlignment, Alignment::Unaligned);
	ImGuiEx::EnumCombo(lang.translate(LangKey::Language).c_str(), settings.settings.language, LanguageSetting::Spanish);

	ImGui::InputInt("max displayed", &settings.settings.maxDisplayed);

	ImGui::Separator();

	MainWindow::DrawStyleSettingsSubMenu();
}

void KillproofUI::DrawContent() {
	// lock the mutexes, before we access sensible data
	std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);

	// Reset Row counter
	mCurrentRow = 0;

	auto& settings = Settings::instance();

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
	if (!extrasLoaded && !settings.settings.hideExtrasMessage) {
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
	if (settings.settings.showControls) {
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
	Alignment alignment = settings.settings.alignment;
	Alignment headerAlignment = settings.settings.headerAlignment;
	const int columnCount = static_cast<int>(Killproof::FINAL_ENTRY) + 4;

	ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable |
						  ImGuiTableFlags_Reorderable | ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX | ImGuiTableFlags_ScrollY;

	ImVec2 outerSize (0.f, getMaxHeightActive() ? mCurrentCursorPos : 0.f);

	if (ImGui::BeginTable("kp.me", columnCount, tableFlags, outerSize)) {
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
		ImGuiTableColumnIdx first = 0;
		for (int i = 0; i <= table->ColumnsCount; ++i) {
			if (table->EnabledMaskByDisplayOrder & ((ImU64)1 << i)) {
				first = table->DisplayOrderToIndex[i];
				break;
			}
		}

		ImGuiTableColumnFlags columnFlags;
		columnFlags = ImGuiTableColumnFlags_PreferSortDescending;
		if (first == 0) {
			columnFlags |= ImGuiTableColumnFlags_IndentEnable;
		}
		ImGui::TableSetupColumn("#", columnFlags, 0, joinTimeId);

		columnFlags = ImGuiTableColumnFlags_PreferSortDescending;
		if (first == 1) {
			columnFlags |= ImGuiTableColumnFlags_IndentEnable;
		}
		ImGui::TableSetupColumn(accountName.c_str(), columnFlags, 0, accountNameId);

		columnFlags = ImGuiTableColumnFlags_PreferSortDescending;
		if (first == 2) {
			columnFlags |= ImGuiTableColumnFlags_IndentEnable;
		}
		ImGui::TableSetupColumn(charName.c_str(), columnFlags, 0, characterNameId);

		columnFlags = ImGuiTableColumnFlags_PreferSortDescending;
		if (first == 3) {
			columnFlags |= ImGuiTableColumnFlags_IndentEnable;
		}
		ImGui::TableSetupColumn(killproofName.c_str(), columnFlags, 0, killproofId);

		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			Killproof kp = static_cast<Killproof>(i);
			int columnFlags = ImGuiTableColumnFlags_PreferSortDescending;

			if (defaultHidden(kp)) {
				columnFlags |= ImGuiTableColumnFlags_DefaultHide;
			}

			ImGui::TableSetupColumn(toString(kp).c_str(), columnFlags, 0.f, static_cast<ImU32>(kp));
		}

		ImGui::TableSetupScrollFreeze(0, 1);

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
				if (settings.settings.headerText) {
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

						auto tiedTimeA = std::tie(joinedTimeA.wYear, joinedTimeA.wMonth, joinedTimeA.wDay, joinedTimeA.wHour, joinedTimeA.wMinute, joinedTimeA.wSecond);
						auto tiedTimeB = std::tie(joinedTimeB.wYear, joinedTimeB.wMonth, joinedTimeB.wDay, joinedTimeB.wHour, joinedTimeB.wMinute, joinedTimeB.wSecond);

						if (descend) {
							return tiedTimeA < tiedTimeB;
						}
						return tiedTimeA > tiedTimeB;
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
			if (!(!settings.settings.showPrivateAccounts && player.status == LoadingStatus::NoDataAvailable)) {
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

			newRow();
		}

		ImGui::EndTable();
	}
}

void KillproofUI::newRow() {
	if (mCurrentRow < Settings::instance().settings.maxDisplayed) {
		SetMaxHeightCursorPos();
	}

	++mCurrentRow;
}

void KillproofUI::drawTextColumn(bool* open, const char* text, const char* username, const std::atomic<LoadingStatus>& status, bool treeNode, bool first, bool
                                 isCommander) {
	if (treeNode) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;
		if (Settings::instance().settings.showLinkedByDefault) {
			treeNodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
		}

		std::string actualText(text);
		actualText.append("###");
		actualText.append(username);

		*open = ImGuiEx::TreeNodeEx(actualText.c_str(), treeNodeFlags, isCommander && Settings::instance().settings.showCommander ? iconLoader.getTexture(ID_Commander_White) : nullptr);
		ImGui::PopStyleVar();
	} else {
		if (isCommander && Settings::instance().settings.showCommander) {
			float size = ImGui::GetFontSize();
			ImGui::Image(iconLoader.getTexture(ID_Commander_White), ImVec2(size, size));
			ImGui::SameLine();
		}
		ImGui::TextUnformatted(text);
		if (status == LoadingStatus::Loaded && ImGui::IsItemClicked()) {
			// Open users kp.me in the browser
			openInBrowser(username);
		}
	}
}

bool KillproofUI::drawRow(const Alignment& alignment, const SYSTEMTIME* joinTime, const char* username, const char* characterName, const char* killproofId,
						  const std::atomic<LoadingStatus>& status,
						  kpFunction killproofsFun, kpFunction coffersFun, kpFunction kpOverallFun, bool treeNode, bool isCommander) {
	ImGui::TableNextRow();

	bool open = false;

	// find first column that is visible
	ImGuiTableColumnIdx first = 0;
	for (int i = 0; i <= table->ColumnsCount; ++i) {
		if (table->EnabledMaskByDisplayOrder & ((ImU64)1 << i)) {
			first = table->DisplayOrderToIndex[i];
			break;
		}
	}

	// #
	if (ImGui::TableNextColumn() && joinTime) {
		drawTextColumn(&open, std::format("{:02d}:{:02d}:{:02d}", joinTime->wHour, joinTime->wMinute, joinTime->wSecond).c_str(), username, status,
		               first == ImGui::TableGetColumnIndex() && treeNode, first == ImGui::TableGetColumnIndex(), false);
	}

	bool usernameEnabled = true;
	for (auto i = 0, j = 0; i < table->DisplayOrderToIndex.size(); ++i) {
		if (table->DisplayOrderToIndex[i] == 1 && table->EnabledMaskByDisplayOrder & (ImU64)1 << i) {
			usernameEnabled = true;
			break;
		}
		if (table->DisplayOrderToIndex[i] == 2 && table->EnabledMaskByDisplayOrder & (ImU64)1 << i) {
			usernameEnabled = false;
			break;
		}
	}
	// username
	if (ImGui::TableNextColumn()) {
		drawTextColumn(&open, username, username, status, first == ImGui::TableGetColumnIndex() && treeNode, first == ImGui::TableGetColumnIndex(), isCommander && usernameEnabled);
	}

	// charactername
	if (ImGui::TableNextColumn()) {
		drawTextColumn(&open, characterName, username, status, first == ImGui::TableGetColumnIndex() && treeNode, first == ImGui::TableGetColumnIndex(), isCommander && !usernameEnabled);
	}

	// killproofID
	if (ImGui::TableNextColumn()) {
		drawTextColumn(&open, killproofId, username, status, first == ImGui::TableGetColumnIndex() && treeNode, first == ImGui::TableGetColumnIndex(), false);
	}

	for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
		if (ImGui::TableNextColumn()) {
			Killproof kp = static_cast<Killproof>(i);
			amountVal totalAmount = kpOverallFun(kp);

			if (status == LoadingStatus::LoadingById || status == LoadingStatus::LoadingByChar) {
				ImGuiEx::SpinnerAligned("loadingSpinner", ImGui::GetTextLineHeight() / 4.f, 1.f, ImGui::GetColorU32(ImGuiCol_Text), Settings::instance().settings.alignment);
			} else if (totalAmount == -1 || status != LoadingStatus::Loaded) {
				ImGuiEx::AlignedTextColumn(alignment, "%s", Settings::instance().settings.blockedDataText.c_str());
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
