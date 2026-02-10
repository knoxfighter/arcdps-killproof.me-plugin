#include "KillproofUITable.h"

#include "Settings.h"
#include "Player.h"
#include "resource.h"

template<bool Linked>
bool KillproofUITable::drawRow(TableColumnIdx pFirstColumnIndex, const Player& pPlayer, bool pHasLinked, bool pTotal, bool pTotalText) {
	NextRow();

	bool accountNameEnabled = true;
	for (auto i = 0; i < mTable.DisplayOrderToIndex.size(); ++i) {
		// the most left of 1 or 2 (username and charname) which is also enabled
		if (mTable.DisplayOrderToIndex[i] == 1 && mTable.EnabledMaskByDisplayOrder.test(i)) {
			accountNameEnabled = true;
			break;
		}
		if (mTable.DisplayOrderToIndex[i] == 2 && mTable.EnabledMaskByDisplayOrder.test(i)) {
			accountNameEnabled = false;
			break;
		}
	}

	bool open = false;

	for (const MainTableColumn& column : COLUMN_SETUP) {
		if (NextColumn()) {
			const bool first = pFirstColumnIndex == GetColumnIndex();

			if (column.UserId == JOIN_TIME_ID && !pTotalText) {
				if constexpr (!Linked) {
					// #
					SYSTEMTIME joinedTime = pPlayer.joinedTime;
					drawTextColumn(open, std::format("{:02d}:{:02d}:{:02d}", joinedTime.wHour, joinedTime.wMinute, joinedTime.wSecond).c_str(), pPlayer.username, pPlayer.status,
					               first && pHasLinked, false);
					
				}
				continue;
			}
			if (column.UserId == ACCOUNT_NAME_ID) {
				if (!pTotalText) {
					drawTextColumn<true>(open, pPlayer.username.c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, pPlayer.commander && accountNameEnabled);
				} else if (accountNameEnabled) {
					drawTextColumn(open, Localization::STranslate(KMT_Overall).data(), pPlayer.username, pPlayer.status, first && pHasLinked, false);
				}
				continue;
			}
			if (column.UserId == CHARACTER_NAME_ID) {
				if (!pTotalText) {
					drawTextColumn<true>(open, pPlayer.characterName.c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, pPlayer.commander && !accountNameEnabled);
				} else if (!accountNameEnabled) {
					drawTextColumn(open, Localization::STranslate(KMT_Overall).data(), pPlayer.username, pPlayer.status, first && pHasLinked, false);
				}
				continue;
			}

			if (column.UserId == KILLPROOF_ID_ID) {
				drawTextColumn<true>(open, pPlayer.killproofId.c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, false);
				continue;
			}

			if (column.UserId == SUBGROUP_ID) {
				// subgroups are zero based and ui is one based
				drawTextColumn(open, std::to_string(pPlayer.subgroup + 1).c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, false);
				continue;
			}

			const auto& killproof = magic_enum::enum_cast<Killproof>(column.UserId);
			if (killproof.has_value()) {
				Killproof kp = killproof.value();
				const std::optional<amountVal> totalAmount = pTotal && pHasLinked || pTotalText ? pPlayer.getKpOverallTotal(kp) : pPlayer.getKpOverall(kp);

				if (pPlayer.status == LoadingStatus::LoadingById || pPlayer.status == LoadingStatus::LoadingByChar) {
					SpinnerAligned("loadingSpinner", ImGui::GetTextLineHeight() / 4.f, 1.f, ImGui::GetColorU32(ImGuiCol_Text));
				} else if (!totalAmount.has_value() || (pPlayer.status != LoadingStatus::Loaded && pPlayer.status != LoadingStatus::LoadedByLinked)) {
					drawTextColumn<false, true>(open, Settings::instance().settings.blockedDataText.c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, false);
				} else {
					drawTextColumn<false, true>(open, std::to_string(totalAmount.value()).c_str(), pPlayer.username, pPlayer.status, first && pHasLinked, false);

					if (IsCurrentColumnHovered()) {
						ImGui::BeginTooltip();
						std::string kpText = std::format("{}: {}", Localization::STranslate(KMT_Killproofs), (pTotal && pHasLinked || pTotalText ? pPlayer.getKillproofsTotal(kp) : pPlayer.getKillproofs(kp)).value_or(0));
						ImGui::TextUnformatted(kpText.c_str());
						const std::optional<amountVal> coffers = pTotal && pHasLinked || pTotalText ? pPlayer.getCoffersTotal(kp) : pPlayer.getCoffers(kp);
						if (coffers.has_value()) {
							std::string cofferText = std::format("{}: {}", Localization::STranslate(KMT_Coffers), coffers.value());
							ImGui::TextUnformatted(cofferText.c_str());
						}
						ImGui::EndTooltip();
					}
				}
				continue;
			}
		}
	}

	return open;
}

template<bool OpenBrowser, bool AlignmentActive>
void KillproofUITable::drawTextColumn(bool& pOpen, const char* pText, const std::string& pUsername, const std::atomic<LoadingStatus>& pStatus, bool pTreeNode, bool
                                      pIsCommander) {
	if (pTreeNode) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.f, 0.f));

		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_FramePadding;
		if (Settings::instance().settings.showLinkedByDefault) {
			treeNodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
		}

		if (pIsCommander && Settings::instance().settings.showCommander) {
			float size = ImGui::GetFontSize();
			ImGui::Image(draw_texture(KillproofIcons::Commander_White), ImVec2(size, size));
			ImGui::SameLine();
		}
		pOpen = ImGuiEx::TreeNodeEx(std::format("{}###{}", pText, pUsername).c_str(), treeNodeFlags, nullptr);
		ImGui::PopStyleVar();
	} else {
		if (pIsCommander && Settings::instance().settings.showCommander) {
			float size = ImGui::GetFontSize();
			ImGui::Image(draw_texture(KillproofIcons::Commander_White), ImVec2(size, size));
			ImGui::SameLine();
		}
		if constexpr (AlignmentActive) {
			AlignedTextColumn(pText);
		} else {
			ImGui::TextUnformatted(pText);
		}

		if constexpr (OpenBrowser) {
			if (pStatus == LoadingStatus::Loaded && ImGui::IsItemClicked()) {
				// Open users kp.me in the browser
				openInBrowser(pUsername);
			}
		}
	}
}

void KillproofUITable::openInBrowser(const std::string& username) {
	const auto& string = std::format("https://killproof.me/proof/{}", username);
	std::thread([string] {
		ShellExecuteA(nullptr, nullptr, string.c_str(), nullptr, nullptr, SW_SHOW);
	}).detach();
}

void KillproofUITable::DrawRows(TableColumnIdx pFirstColumnIndex) {
	const auto& settingsObject = Settings::instance().settings;
	bool showPrivateAccounts = settingsObject.showPrivateAccounts;
	bool showLinkedTotalsOnUser = settingsObject.showLinkedTotalsOnUser;

	// List of all players
	for (const std::string& trackedPlayer : trackedPlayers) {
		const Player& player = cachedPlayers.at(trackedPlayer);

		// hide player without data, when setting is active
		if (!(!showPrivateAccounts && player.status == LoadingStatus::NoDataAvailable)) {
			bool open = drawRow(pFirstColumnIndex, player, !player.linkedAccounts.empty(), showLinkedTotalsOnUser);
			if (open) {
				for (const std::string& linkedAccount : player.linkedAccounts) {
					Player& linkedPlayer = cachedPlayers.at(linkedAccount);
					drawRow<true>(pFirstColumnIndex, linkedPlayer, false);
				}
				// draw Row for overall amount
				if (!showLinkedTotalsOnUser) {
					drawRow<true>(pFirstColumnIndex, player, false, true, true);
				} else {
					drawRow<true>(pFirstColumnIndex, player, false);
				}

				ImGui::TreePop();
			}

			EndMaxHeightRow();
		}
	}
}

void KillproofUITable::Sort(const ImGuiTableColumnSortSpecs* mColumnSortSpecs) {
	const bool descend = mColumnSortSpecs->SortDirection == ImGuiSortDirection_Descending;

	if (mColumnSortSpecs->ColumnUserID == JOIN_TIME_ID) {
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
		return;
	}
	if (mColumnSortSpecs->ColumnUserID == ACCOUNT_NAME_ID) {
		// sort by account name. Account name is the value we used in trackedPlayers, so nothing more to do
		std::ranges::sort(trackedPlayers, [descend](std::string playerAName, std::string playerBName) {
			std::ranges::transform(playerAName, playerAName.begin(), [](unsigned char c) { return std::tolower(c); });
			std::ranges::transform(playerBName, playerBName.begin(), [](unsigned char c) { return std::tolower(c); });

			if (descend) {
				return playerAName < playerBName;
			}
			return playerAName > playerBName;
		});
		return;
	}
	if (mColumnSortSpecs->ColumnUserID == CHARACTER_NAME_ID) {
		// sort by character name
		std::ranges::sort(trackedPlayers, [descend](const std::string& playerAName, const std::string& playerBName) {
			std::string playerAChar = cachedPlayers.at(playerAName).characterName;
			std::string playerBChar = cachedPlayers.at(playerBName).characterName;

			std::ranges::transform(playerAChar, playerAChar.begin(), [](unsigned char c) { return std::tolower(c); });
			std::ranges::transform(playerBChar, playerBChar.begin(), [](unsigned char c) { return std::tolower(c); });

			if (descend) {
				return playerAChar < playerBChar;
			}
			return playerAChar > playerBChar;
		});
		return;
	}
	if (mColumnSortSpecs->ColumnUserID == KILLPROOF_ID_ID) {
		// sort by character name
		std::ranges::sort(trackedPlayers, [descend](const std::string& playerAName, const std::string& playerBName) {
			const std::string& playerAChar = cachedPlayers.at(playerAName).killproofId;
			const std::string& playerBChar = cachedPlayers.at(playerBName).killproofId;

			if (descend) {
				return playerAChar < playerBChar;
			}
			return playerAChar > playerBChar;
		});
		return;
	}
	if (mColumnSortSpecs->ColumnUserID == SUBGROUP_ID) {
		// sort by subgroup
		std::ranges::sort(trackedPlayers, [descend](const std::string& playerAName, const std::string& playerBName) {
			uint8_t playerAGroup = cachedPlayers.at(playerAName).subgroup;
			uint8_t playerBGroup = cachedPlayers.at(playerBName).subgroup;

			if (descend) {
				return playerAGroup > playerBGroup;
			}
			return playerAGroup < playerBGroup;
		});
		return;
	}
	const auto& killproof = magic_enum::enum_cast<Killproof>(mColumnSortSpecs->ColumnUserID);
	if (killproof.has_value()) {
		// sort by any amount of KP
		const auto kp = killproof.value();
		bool showLinkedTotalsOnUser = Settings::instance().settings.showLinkedTotalsOnUser;
		std::ranges::sort(trackedPlayers, [&kp, descend, showLinkedTotalsOnUser](const std::string& playerAName, const std::string& playerBName) {
			// get player object of name
			const Player& playerA = cachedPlayers.at(playerAName);
			const Player& playerB = cachedPlayers.at(playerBName);

			
			// const auto& amountAOpt = playerA.getKpOverall(kp);
			const auto& amountAOpt = showLinkedTotalsOnUser && !playerA.linkedAccounts.empty() ? playerA.getKpOverallTotal(kp) : playerA.getKpOverall(kp);
			const auto& amountBOpt = showLinkedTotalsOnUser && !playerB.linkedAccounts.empty() ? playerB.getKpOverallTotal(kp) : playerB.getKpOverall(kp);

			amountVal amountA = amountAOpt ? amountAOpt.value() : -1;
			amountVal amountB = amountBOpt ? amountBOpt.value() : -1;

			// descending: the more the higher up it gets
			if (descend) {
				return amountA > amountB;
			}
			return amountA < amountB;
		});
	}
}

Alignment& KillproofUITable::getAlignment() {
	return Settings::instance().settings.alignment;
}

Alignment& KillproofUITable::getHeaderAlignment() {
	return Settings::instance().settings.headerAlignment;
}

std::string KillproofUITable::getTableId() {
	return "kp.me";
}

int& KillproofUITable::getMaxDisplayed() {
	return Settings::instance().settings.maxDisplayed;
}

bool& KillproofUITable::getShowAlternatingBackground() {
	return Settings::instance().settings.showAlternatingRowBackground;
}

KillproofUITable::TableSettings& KillproofUITable::getTableSettings() {
	return Settings::instance().settings.tableSettings;
}

bool& KillproofUITable::getHighlightHoveredRows() {
	return Settings::instance().settings.highlightHoveredRows;
}

const char* KillproofUITable::getCategoryName(const std::string& pCat) {
	if (pCat == "1") return Localization::STranslate(KMT_Raids).data();
	if (pCat == "2") return Localization::STranslate(KMT_Fractals).data();
	if (pCat == "3") return Localization::STranslate(KMT_Strikes).data();
	if (pCat == "4") return Localization::STranslate(KMT_Misc).data();
	if (pCat == "1.1") return "W1";
	if (pCat == "1.2") return "W2";
	if (pCat == "1.3") return "W3";
	if (pCat == "1.4") return "W4";
	if (pCat == "1.5") return "W5";
	if (pCat == "1.6") return "W6";
	if (pCat == "1.7") return "W7";
	if (pCat == "1.8") return "W8";
	return "";
}

void KillproofUITable::MigrateSettings() {
	auto& tableSettings = Settings::instance().settings.tableSettings;
	if (tableSettings.Version == 1) {
		tableSettings.Version = 2;
	}

	if (tableSettings.Version == 2) {
		tableSettings.Columns.clear();
		tableSettings.Version = 3;
		tableSettings.RefScale = 0;
		tableSettings.SaveFlags = 0;
	}
}

bool& KillproofUITable::getCustomColumnsActive() {
	return Settings::instance().settings.showBasedOnMap;
}

bool& KillproofUITable::getShowHeaderAsText() {
	return Settings::instance().settings.showHeaderText;
}
