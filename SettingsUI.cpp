#include "SettingsUI.h"

#include <Windows.h>

#include "Settings.h"

#define windowWidth 800
#define leftItemWidth  200
#define rightItemWidth 600

SettingsUI::SettingsUI() {
	Settings& settings = Settings::instance();

	// set all buffer to the values from Settings

	int killProofKey = settings.getKillProofKey();
	// copy in the string represantation of the key ID
	strcpy_s(shortcut, std::to_string(killProofKey).c_str());
	// convert virtual key to vsc key
	UINT vscKey = MapVirtualKeyA(killProofKey, MAPVK_VK_TO_VSC);
	// get the name representation of the key
	GetKeyNameTextA((vscKey << 16), shortCutRealName, 32);

	strcpy_s(blockedDataText, settings.settings.blockedDataText.c_str());
}

void SettingsUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSize(ImVec2(windowWidth, 650), ImGuiCond_FirstUseEver);
	// set min size of the object
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(150, 50));
	ImGui::Begin(title, p_open, flags);

	// set frame padding smaller (small buttons)
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

	Settings& settings = Settings::instance();

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	ImGui::Text("Shortcut to open killproofs menu:");
	ImGui::SameLine();
	ImGui::PushItemWidth(30);
	if (ImGui::InputText("##shortcut", shortcut, 64)) {
		try {
			const int keyId = std::stoi(shortcut);
			settings.settings.killproofKey = keyId;
			// convert virtual key to vsc key
			UINT vscKey = MapVirtualKeyA(keyId, MAPVK_VK_TO_VSC);
			// get the name representation of the key
			GetKeyNameTextA((vscKey << 16), shortCutRealName, 32);
		} catch ([[maybe_unused]] const std::invalid_argument& e) {

		} catch ([[maybe_unused]] const std::out_of_range& e) {

		}
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text(shortCutRealName);

	// input for data private
	ImGui::PushItemWidth(50);
	if (ImGui::InputText("Text to display when data is unavailable/private", blockedDataText, sizeof blockedDataText)) {
		if (strlen(blockedDataText) == 0) {
			settings.settings.blockedDataText = " ";
		}
		else {
			settings.settings.blockedDataText = blockedDataText;
		}
	}
	ImGui::PopItemWidth();

	ImGui::Checkbox("hide players without killproof.me account", &settings.settings.hidePrivateAccount);
	ImGui::Checkbox("Do NOT close killproof.me window on ESC", &settings.settings.disableEscClose);

	ImGui::PopStyleVar();
	ImGui::End();
	ImGui::PopStyleVar();
}
