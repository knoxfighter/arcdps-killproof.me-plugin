#include "SettingsUI.h"

#include <Windows.h>

#include "Settings.h"

#define windowWidth 800
#define leftItemWidth  200
#define rightItemWidth 600

SettingsUI::SettingsUI() {
	Settings& settings = Settings::instance();
	int killProofKey = settings.getKillProofKey();
	// copy in the string represantation of the key ID
	strcpy_s(shortcut, std::to_string(killProofKey).c_str());
	// convert virtual key to vsc key
	UINT vscKey = MapVirtualKeyA(killProofKey, MAPVK_VK_TO_VSC);
	// get the name representation of the key
	GetKeyNameTextA((vscKey << 16), shortCutRealName, 32);
}

void SettingsUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSize(ImVec2(windowWidth, 650), ImGuiSetCond_FirstUseEver);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(150, 50));
	ImGui::Begin(title, p_open, flags);

	Settings& settings = Settings::instance();

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	ImGui::Text("Shortcut to open killproofs menu:");
	ImGui::SameLine();
	ImGui::PushItemWidth(30);
	if (ImGui::InputText("##shortcut", shortcut, 64)) {
		const int keyId = std::stoi(shortcut);
		settings.settings.killproofKey = keyId;
		// convert virtual key to vsc key
		UINT vscKey = MapVirtualKeyA(keyId, MAPVK_VK_TO_VSC);
		// get the name representation of the key
		GetKeyNameTextA((vscKey << 16), shortCutRealName, 32);
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::Text(shortCutRealName);

	ImGui::Checkbox("hide players without killproof.me account", &settings.settings.hidePrivateAccount);

	ImGui::Separator();

	// A list of all available KPs. Can be activated and deactivated here
	ImGui::Text("Everything selected is shown in the killproofs menu");

	for (auto& active : settings.getActive()) {
		ImGui::Checkbox(toString(active.first), &active.second);
	}

	ImGui::End();
	ImGui::PopStyleVar(1);
}
