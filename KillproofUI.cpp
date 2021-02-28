#include "KillproofUI.h"

#include <mutex>
#include <Windows.h>

#include "global.h"
#include "Player.h"
#include "Settings.h"
#include "imgui/imgui_internal.h"
#include "Icon.h"
#include "Lang.h"

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
	std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);

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
		ImGui::SetTooltip(Lang::translate(LangKey::AddPlayerTooltip).c_str());
	ImGui::SameLine();
	if (ImGui::Button(Lang::translate(LangKey::AddPlayerText).c_str())) {
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
	if (ImGui::Button(Lang::translate(LangKey::ClearText).c_str())) {
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
		ImGui::SetTooltip(Lang::translate(LangKey::ClearTooltip).c_str());
	}

	// get own player
	const auto& playerIt = cachedPlayers.find(selfAccountName);
	if (playerIt != cachedPlayers.end()) {
		const Player& player = playerIt->second;
		if (player.status == LoadingStatus::Loaded) {
			ImGui::SameLine();
			// static float CopyIdButtonWidth = 100.0f;
			// float pos = CopyIdButtonWidth + ImGui::GetStyle().ItemSpacing.x;
			// pos = ImMax(ImGui::GetCursorPosX(), ImGui::GetWindowWidth() - pos - 1);
			// ImGui::SetCursorPosX(pos);
			if (ImGui::Button(Lang::translate(LangKey::CopyKpIdText).c_str())) {
				// copy ID to clipboard
				//put your text in source
				if (OpenClipboard(NULL))
				{
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
			// CopyIdButtonWidth = ImGui::GetItemRectSize().x;
		}
	}

	/**
	 * TABLE
	 */
	const int columnCount = static_cast<int>(Killproof::FINAL_ENTRY) + 2;

	if (ImGui::BeginTable("kp.me", columnCount,
	                      ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable |
	                      ImGuiTableFlags_RowBg)) {
		ImU32 accountNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 1;
		ImU32 characterNameId = static_cast<ImU32>(Killproof::FINAL_ENTRY) + 2;

		std::string accountName = Lang::translate(LangKey::Accountname);
		std::string charName = Lang::translate(LangKey::Charactername);

		// Header
		ImGui::TableSetupColumn(accountName.c_str(), ImGuiTableColumnFlags_NoReorder, 0, accountNameId);
		ImGui::TableSetupColumn(charName.c_str(), ImGuiTableColumnFlags_NoReorder, 0, characterNameId);

		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			Killproof kp = static_cast<Killproof>(i);
			int columnFlags = 0;

			if (defaultHidden(kp)) {
				columnFlags |= ImGuiTableColumnFlags_DefaultHide;
			}

			ImGui::TableSetupColumn(toString(kp).c_str(), columnFlags, 0.f, static_cast<ImU32>(kp));
		}

		ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

		// accountname header
		ImGui::TableNextColumn();
		ImGui::PushID(0);
		ImGui::TableHeader(accountName.c_str());
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(accountName.c_str());
		}
		ImGui::PopID();

		// charname header
		ImGui::TableNextColumn();
		ImGui::PushID(1);
		ImGui::TableHeader(charName.c_str());
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(charName.c_str());
		}
		ImGui::PopID();

		// header for killproofs
		for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
			if (ImGui::TableNextColumn()) {
				Killproof kp = static_cast<Killproof>(i);
				std::string columnName = toString(kp);
				ImGui::PushID(columnName.c_str());
				if (settings.getShowHeaderText()) {
					TableHeader(columnName.c_str(), true);
				} else {
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					ImGui::Image(icons.at(kp).texture, ImVec2(16, 16));
					ImGui::PopStyleVar();
					ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
					TableHeader(columnName.c_str(), false);
				}

				if (ImGui::IsItemHovered()) {
					ImGui::SetTooltip(columnName.c_str());
				}
				ImGui::PopID();
			}
		}


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
				if (ImGui::TableNextColumn()) {
					ImGui::Text(player.username.c_str());
					if (!(player.status == LoadingStatus::NoDataAvailable) && ImGui::IsItemClicked()) {
						// Open users kp.me in the browser
						openInBrowser(player.username.c_str());
					}
				}

				// charactername
				if (ImGui::TableNextColumn()) {
					ImGui::Text(player.characterName.c_str());
					if (ImGui::IsItemClicked()) {
						// Open users kp.me in the browser
						openInBrowser(player.username.c_str());
					}
				}

				for (int i = 0; i < static_cast<int>(Killproof::FINAL_ENTRY); ++i) {
					if (ImGui::TableNextColumn()) {
						const amountVal amount = player.killproofs.getAmountFromEnum(static_cast<Killproof>(i));
						if (amount == -1 || player.status != LoadingStatus::Loaded) {
							AlignedTextColumn("%s", settings.getBlockedDataText().c_str());
						} else {
							AlignedTextColumn("%i", amount);
						}
					}
				}
			}
		}

		ImGui::EndTable();
	}

	ImGui::End();
}


void KillproofUI::AlignedTextColumn(const char* text, ...) const {
	va_list args;
	va_start(args, text);
	char buf[4096];
	ImFormatStringV(buf, 4096, text, args);
	va_end(args);

	const float posX = ImGui::GetCursorPosX();
	float newX = posX;
	float textWidth = ImGui::CalcTextSize(buf).x;
	float columnWidth = ImGui::GetColumnWidth();

	Alignment alignment = Settings::instance().getAlignment();
	switch (alignment) {
	case Alignment::Left:
		break;
	case Alignment::Center:
		newX = posX + columnWidth / 2 - textWidth / 2;
		break;
	case Alignment::Right:
		newX = posX + columnWidth - textWidth;
		break;
	}

	// Clip to left, if text is bigger than current column
	if (newX < posX) {
		newX = posX;
	}

	ImGui::SetCursorPosX(newX);

	ImGui::TextUnformatted(buf);
}

// This is a copy of `ImGui::TableHeader(const char* label)`
// I removed the line, where the header is printed, so i can use it with image only headers.
//
// Emit a column header (text + optional sort order)
// We cpu-clip text here so that all columns headers can be merged into a same draw call.
// Note that because of how we cpu-clip and display sorting indicators, you _cannot_ use SameLine() after a TableHeader()
void KillproofUI::TableHeader(const char* label, bool show_text) {
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;
	if (window->SkipItems)
		return;

	ImGuiTable* table = g.CurrentTable;
	IM_ASSERT(table != NULL && "Need to call TableHeader() after BeginTable()!");
	IM_ASSERT(table->CurrentColumn != -1);
	const int column_n = table->CurrentColumn;
	ImGuiTableColumn* column = &table->Columns[column_n];

	// Label
	if (label == NULL)
		label = "";
	const char* label_end = ImGui::FindRenderedTextEnd(label);
	ImVec2 label_size = ImGui::CalcTextSize(label, label_end, true);
	ImVec2 label_pos = window->DC.CursorPos;

	// If we already got a row height, there's use that.
	// FIXME-TABLE: Padding problem if the correct outer-padding CellBgRect strays off our ClipRect?
	ImRect cell_r = ImGui::TableGetCellBgRect(table, column_n);
	float label_height = table->RowMinHeight - table->CellPaddingY * 2.0f;
	if (show_text)
		label_height = ImMax(label_size.y, label_height);

	// Calculate ideal size for sort order arrow
	float w_arrow = 0.0f;
	float w_sort_text = 0.0f;
	char sort_order_suf[4] = "";
	const float ARROW_SCALE = 0.65f;
	if ((table->Flags & ImGuiTableFlags_Sortable) && !(column->Flags & ImGuiTableColumnFlags_NoSort)) {
		w_arrow = ImFloor(g.FontSize * ARROW_SCALE + g.Style.FramePadding.x);
		if (column->SortOrder > 0) {
			ImFormatString(sort_order_suf, IM_ARRAYSIZE(sort_order_suf), "%d", column->SortOrder + 1);
			w_sort_text = g.Style.ItemInnerSpacing.x + ImGui::CalcTextSize(sort_order_suf).x;
		}
	}

	// We feed our unclipped width to the column without writing on CursorMaxPos, so that column is still considering for merging.
	float max_pos_x = label_pos.x + w_sort_text + w_arrow;
	if (show_text)
		max_pos_x += label_size.x;
	column->ContentMaxXHeadersUsed = ImMax(column->ContentMaxXHeadersUsed, column->WorkMaxX);
	column->ContentMaxXHeadersIdeal = ImMax(column->ContentMaxXHeadersIdeal, max_pos_x);

	// Keep header highlighted when context menu is open.
	const bool selected = (table->IsContextPopupOpen && table->ContextPopupColumn == column_n && table->InstanceInteracted == table->InstanceCurrent);
	ImGuiID id = window->GetID(label);
	ImRect bb(cell_r.Min.x, cell_r.Min.y, cell_r.Max.x, ImMax(cell_r.Max.y, cell_r.Min.y + label_height + g.Style.CellPadding.y * 2.0f));
	ImGui::ItemSize(ImVec2(0.0f, label_height)); // Don't declare unclipped width, it'll be fed ContentMaxPosHeadersIdeal
	if (!ImGui::ItemAdd(bb, id))
		return;

	//GetForegroundDrawList()->AddRect(cell_r.Min, cell_r.Max, IM_COL32(255, 0, 0, 255)); // [DEBUG]
	//GetForegroundDrawList()->AddRect(bb.Min, bb.Max, IM_COL32(255, 0, 0, 255)); // [DEBUG]

	// Using AllowItemOverlap mode because we cover the whole cell, and we want user to be able to submit subsequent items.
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, ImGuiButtonFlags_AllowItemOverlap);
	if (g.ActiveId != id)
		ImGui::SetItemAllowOverlap();
	if (held || hovered || selected) {
		const ImU32 col = ImGui::GetColorU32(held ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
		//RenderFrame(bb.Min, bb.Max, col, false, 0.0f);
		ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, col, table->CurrentColumn);
		ImGui::RenderNavHighlight(bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);
	} else {
		// Submit single cell bg color in the case we didn't submit a full header row
		if ((table->RowFlags & ImGuiTableRowFlags_Headers) == 0)
			ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImGuiCol_TableHeaderBg), table->CurrentColumn);
	}
	if (held)
		table->HeldHeaderColumn = (ImGuiTableColumnIdx)column_n;
	window->DC.CursorPos.y -= g.Style.ItemSpacing.y * 0.5f;

	// Drag and drop to re-order columns.
	// FIXME-TABLE: Scroll request while reordering a column and it lands out of the scrolling zone.
	if (held && (table->Flags & ImGuiTableFlags_Reorderable) && ImGui::IsMouseDragging(0) && !g.DragDropActive) {
		// While moving a column it will jump on the other side of the mouse, so we also test for MouseDelta.x
		table->ReorderColumn = (ImGuiTableColumnIdx)column_n;
		table->InstanceInteracted = table->InstanceCurrent;

		// We don't reorder: through the frozen<>unfrozen line, or through a column that is marked with ImGuiTableColumnFlags_NoReorder.
		if (g.IO.MouseDelta.x < 0.0f && g.IO.MousePos.x < cell_r.Min.x)
			if (ImGuiTableColumn* prev_column = (column->PrevEnabledColumn != -1) ? &table->Columns[column->PrevEnabledColumn] : NULL)
				if (!((column->Flags | prev_column->Flags) & ImGuiTableColumnFlags_NoReorder))
					if ((column->IndexWithinEnabledSet < table->FreezeColumnsRequest) == (prev_column->IndexWithinEnabledSet < table->FreezeColumnsRequest))
						table->ReorderColumnDir = -1;
		if (g.IO.MouseDelta.x > 0.0f && g.IO.MousePos.x > cell_r.Max.x)
			if (ImGuiTableColumn* next_column = (column->NextEnabledColumn != -1) ? &table->Columns[column->NextEnabledColumn] : NULL)
				if (!((column->Flags | next_column->Flags) & ImGuiTableColumnFlags_NoReorder))
					if ((column->IndexWithinEnabledSet < table->FreezeColumnsRequest) == (next_column->IndexWithinEnabledSet < table->FreezeColumnsRequest))
						table->ReorderColumnDir = +1;
	}

	// Sort order arrow
	const float ellipsis_max = cell_r.Max.x - w_arrow - w_sort_text;
	if ((table->Flags & ImGuiTableFlags_Sortable) && !(column->Flags & ImGuiTableColumnFlags_NoSort)) {
		if (column->SortOrder != -1) {
			float x = ImMax(cell_r.Min.x, cell_r.Max.x - w_arrow - w_sort_text);
			float y = label_pos.y;
			if (column->SortOrder > 0) {
				ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(ImGuiCol_Text, 0.70f));
				ImGui::RenderText(ImVec2(x + g.Style.ItemInnerSpacing.x, y), sort_order_suf);
				ImGui::PopStyleColor();
				x += w_sort_text;
			}
			ImGui::RenderArrow(window->DrawList, ImVec2(x, y), ImGui::GetColorU32(ImGuiCol_Text),
			                   column->SortDirection == ImGuiSortDirection_Ascending ? ImGuiDir_Up : ImGuiDir_Down, ARROW_SCALE);
		}

		// Handle clicking on column header to adjust Sort Order
		if (pressed && table->ReorderColumn != column_n) {
			ImGuiSortDirection sort_direction = ImGui::TableGetColumnNextSortDirection(column);
			ImGui::TableSetColumnSortDirection(column_n, sort_direction, g.IO.KeyShift);
		}
	}

	// Render clipped label. Clipping here ensure that in the majority of situations, all our header cells will
	// be merged into a single draw call.
	//window->DrawList->AddCircleFilled(ImVec2(ellipsis_max, label_pos.y), 40, IM_COL32_WHITE);
	if (show_text)
		ImGui::RenderTextEllipsis(window->DrawList, label_pos, ImVec2(ellipsis_max, label_pos.y + label_height + g.Style.FramePadding.y), ellipsis_max, ellipsis_max, label, label_end, &label_size);

	// const bool text_clipped = label_size.x > (ellipsis_max - label_pos.x);
	// if (text_clipped && hovered && g.HoveredIdNotActiveTimer > g.TooltipSlowDelay)
	// 	ImGui::SetTooltip("%.*s", (int)(label_end - label), label);

	// We don't use BeginPopupContextItem() because we want the popup to stay up even after the column is hidden
	if (ImGui::IsMouseReleased(1) && ImGui::IsItemHovered())
		ImGui::TableOpenContextMenu(column_n);
}
