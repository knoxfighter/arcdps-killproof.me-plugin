#include "SettingsUI.h"

#include <Windows.h>

#include "Player.h"
#include "Settings.h"
#include "global.h"
#include "Lang.h"

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

void SettingsUI::draw() {
	Settings& settings = Settings::instance();

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	ImGui::Text(Lang::translate(LangKey::SettingsShortcutText).c_str());
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
	if (ImGui::InputText(Lang::translate(LangKey::SettingsBlockedText).c_str(), blockedDataText, sizeof blockedDataText)) {
		if (strlen(blockedDataText) == 0) {
			settings.settings.blockedDataText = " ";
		}
		else {
			settings.settings.blockedDataText = blockedDataText;
		}
	}
	ImGui::PopItemWidth();

	ImGui::Checkbox(Lang::translate(LangKey::SettingsHidePrivateText).c_str(), &settings.settings.hidePrivateAccount);
	ImGui::Checkbox(Lang::translate(LangKey::SettingsDisableESCText).c_str(), &settings.settings.disableEscClose);
	ImGui::Checkbox(Lang::translate(LangKey::SettingsShowHeaderText).c_str(), &settings.settings.showHeaderText);

	if (ImGui::BeginCombo(Lang::translate(LangKey::Alignment).c_str(), to_string(settings.settings.alignment).c_str())) {
		alignmentSelectable(Alignment::Left, settings);
		alignmentSelectable(Alignment::Center, settings);
		alignmentSelectable(Alignment::Right, settings);

		ImGui::EndCombo();
	}

	if (ImGui::Button(Lang::translate(LangKey::SettingsClearCacheText).c_str())) {
		std::scoped_lock<std::mutex, std::mutex> guard(cachedPlayersMutex, trackedPlayersMutex);

		// get all accountnames and charnames
		std::map<std::string, std::string> userToCharNames;
		for (std::string trackedPlayer : trackedPlayers) {
			const Player& player = cachedPlayers.at(trackedPlayer);
			userToCharNames[trackedPlayer] = player.characterName;
		}

		// clear the cache
		cachedPlayers.clear();

		// refill the cache with only tracked players
		for (const auto& userToCharName : userToCharNames) {
			const auto& tryEmplace = cachedPlayers.try_emplace(userToCharName.first, userToCharName.first, userToCharName.second);

			// load kp.me data if less than 10 people tracked
			loadKillproofsSizeChecked(tryEmplace.first->second);
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(Lang::translate(LangKey::SettingsClearCacheTooltip).c_str());
}

void SettingsUI::alignmentSelectable(Alignment select_alignment, Settings& settings) {
	std::string new_alignment_text = to_string(select_alignment);
	if (ImGui::Selectable(new_alignment_text.c_str())) {
		settings.settings.alignment = select_alignment;
	}
}
