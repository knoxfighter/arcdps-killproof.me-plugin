#include "WindowSettingsUI.h"

#include "global.h"
#include "Killproofs.h"
#include "Lang.h"
#include "Settings.h"
#include "extension/Widgets.h"

WindowSettingsUI windowSettingsUI;

WindowSettingsUI::WindowSettingsUI() {
	strcpy_s(blockedDataText, settings.settings.blockedDataText.c_str());
}

void WindowSettingsUI::draw(ImGuiTable* table, ImGuiWindow* currentRootWindow) {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

	if (ImGui::BeginMenu(lang.translate(LangKey::SettingsColumnSetup).c_str())) {
		ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

		// username
		ImGuiEx::MenuItemTableColumnVisibility(table, 0);
		// charname
		ImGuiEx::MenuItemTableColumnVisibility(table, 1);

		// Raids
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsGroup).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::li) + 2);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ld) + 2);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::liLd) + 2);

			// W1
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW1Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::vg) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::gorse) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sabetha) + 2);

				ImGui::EndMenu();
			}

			// W2
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW2Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sloth) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::matthias) + 2);

				ImGui::EndMenu();
			}

			// W3
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW3Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::escort) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::kc) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::xera) + 2);

				ImGui::EndMenu();
			}

			// W4
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW4Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::cairn) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::mo) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::samarog) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::deimos) + 2);

				ImGui::EndMenu();
			}

			// W5
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW5Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::desmina) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::river) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::statues) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::dhuum) + 2);

				ImGui::EndMenu();
			}

			// W6
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW6Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ca) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::twins) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::qadim) + 2);

				ImGui::EndMenu();
			}

			// W7
			if (ImGui::BeginMenu(lang.translate(LangKey::SettingsRaidsW7Group).c_str())) {
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::sabir) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::adina) + 2);
				ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::qadim2) + 2);

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		// Fractals
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsFractalsGroup).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::uce) + 2);
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::ufe) + 2);

			ImGui::EndMenu();
		}

		// Strikes
		if (ImGui::BeginMenu(lang.translate(LangKey::SettingsStrikesGruop).c_str())) {
			ImGuiEx::MenuItemTableColumnVisibility(table, static_cast<int>(Killproof::boneskinnerVial) + 2);

			ImGui::EndMenu();
		}

		ImGui::PopItemFlag();

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu(lang.translate(LangKey::SettingsStyle).c_str())) {
		ImGui::Checkbox(lang.translate(LangKey::SettingsShowHeaderText).c_str(), &settings.settings.showHeaderText);
		ImGui::Checkbox(lang.translate(LangKey::SettingsHidePrivateText).c_str(), &settings.settings.hidePrivateAccount);
		ImGui::Checkbox(lang.translate(LangKey::SettingsHideHeaderButtons).c_str(), &settings.settings.hideControls);
		ImGui::Checkbox(lang.translate(LangKey::SettingsShowOverallByDefault).c_str(), &settings.settings.showOverallByDefault);
		ImGui::Checkbox(lang.translate(LangKey::SettingsShowHeader).c_str(), &settings.settings.showHeader);

		// input for data private
		ImGui::PushItemWidth(50);
		if (ImGui::InputText(lang.translate(LangKey::SettingsBlockedText).c_str(), blockedDataText, sizeof blockedDataText)) {
			if (strlen(blockedDataText) == 0) {
				settings.settings.blockedDataText = " ";
			} else {
				settings.settings.blockedDataText = blockedDataText;
			}
		}
		ImGui::PopItemWidth();

		if (ImGui::BeginCombo(lang.translate(LangKey::Alignment).c_str(), to_string(settings.settings.alignment).c_str())) {
			ImGuiEx::Selectable(settings.settings.alignment, Alignment::Left);
			ImGuiEx::Selectable(settings.settings.alignment, Alignment::Center);
			ImGuiEx::Selectable(settings.settings.alignment, Alignment::Right);

			ImGui::EndCombo();
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu(lang.translate(LangKey::SettingsPosition).c_str())) {
		ImGuiEx::EnumRadioButton(position, Position::Manual, settings.settings.position);

		ImGuiEx::EnumRadioButton(position, Position::ScreenRelative, settings.settings.position);
		if (position == static_cast<int>(Position::ScreenRelative)) {
			ImGui::Indent(15.f);

			ImGui::PushID("cornerPositionRadioButton");
			ImGuiEx::EnumRadioButton(cornerPosition, CornerPosition::TopLeft, settings.settings.cornerPosition);
			ImGuiEx::EnumRadioButton(cornerPosition, CornerPosition::TopRight, settings.settings.cornerPosition);
			ImGuiEx::EnumRadioButton(cornerPosition, CornerPosition::BottomLeft, settings.settings.cornerPosition);
			ImGuiEx::EnumRadioButton(cornerPosition, CornerPosition::BottomRight, settings.settings.cornerPosition);
			ImGui::PopID();

			ImGui::PushItemWidth(80.f);
			ImGui::DragFloat("x", &settings.settings.cornerVector.x);
			ImGui::DragFloat("y", &settings.settings.cornerVector.y);
			ImGui::PopItemWidth();

			ImGui::Unindent(15.f);
		}

		ImGuiEx::EnumRadioButton(position, Position::WindowRelative, settings.settings.position);
		if (position == static_cast<int>(Position::WindowRelative)) {
			ImGui::Indent(15.f);

			ImGui::TextUnformatted(lang.translate(LangKey::SettingsFromAnchorPanelCorner).c_str());
			ImGui::PushID("anchorPanelCornerPositionRadioButton");
			ImGuiEx::EnumRadioButton(anchorPanelCornerPosition, CornerPosition::TopLeft, settings.settings.anchorPanelCornerPosition);
			ImGuiEx::EnumRadioButton(anchorPanelCornerPosition, CornerPosition::TopRight, settings.settings.anchorPanelCornerPosition);
			ImGuiEx::EnumRadioButton(anchorPanelCornerPosition, CornerPosition::BottomLeft, settings.settings.anchorPanelCornerPosition);
			ImGuiEx::EnumRadioButton(anchorPanelCornerPosition, CornerPosition::BottomRight, settings.settings.anchorPanelCornerPosition);
			ImGui::PopID();

			ImGui::TextUnformatted(lang.translate(LangKey::SettingsToThisPanelCorner).c_str());
			ImGui::PushID("selfPanelCornerPositionRadioButton");
			ImGuiEx::EnumRadioButton(selfPanelCornerPosition, CornerPosition::TopLeft, settings.settings.selfPanelCornerPosition);
			ImGuiEx::EnumRadioButton(selfPanelCornerPosition, CornerPosition::TopRight, settings.settings.selfPanelCornerPosition);
			ImGuiEx::EnumRadioButton(selfPanelCornerPosition, CornerPosition::BottomLeft, settings.settings.selfPanelCornerPosition);
			ImGuiEx::EnumRadioButton(selfPanelCornerPosition, CornerPosition::BottomRight, settings.settings.selfPanelCornerPosition);
			ImGui::PopID();

			ImGui::PushItemWidth(80.f);
			ImGui::DragFloat("x", &settings.settings.cornerVector.x);
			ImGui::DragFloat("y", &settings.settings.cornerVector.y);
			ImGui::PopItemWidth();

			ImGuiID shownWindowName = settings.settings.fromWindowID;
			ImGuiWindow* selectedWindow = ImGui::FindWindowByID(shownWindowName);
			std::string selectedWindowName;
			if (selectedWindow) {
				selectedWindowName = selectedWindow->Name;
				const auto findRes = selectedWindowName.find('#');
				if (findRes != std::string::npos) {
					selectedWindowName = selectedWindowName.substr(0, findRes);
				}
			}

			if (ImGui::BeginCombo(lang.translate(LangKey::SettingsFromWindowName).c_str(), selectedWindowName.c_str())) {
				for (ImGuiWindow* window : GImGui->Windows) {
					if (!window->Hidden) {
						std::string windowName = window->Name;
						if (window->ParentWindow || window->ID == currentRootWindow->ID || windowName.find("Tooltip_") != std::string::npos
							|| windowName.find("Default") != std::string::npos || windowName.find('/') != std::string::npos) {
							continue;
						}

						const auto findRes = windowName.find('#');
						if (findRes != std::string::npos) {
							windowName = windowName.substr(0, findRes);
						}

						if (ImGui::Selectable(windowName.c_str())) {
							settings.settings.fromWindowID = window->ID;
						}
					}
				}
				ImGui::EndCombo();
			}

			ImGui::Unindent();
		}

		ImGui::EndMenu();
	}

	ImGui::PopStyleVar();
}
