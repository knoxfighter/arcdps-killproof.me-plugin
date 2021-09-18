#include "SettingsUI.h"

#include <Windows.h>

#include "Player.h"
#include "Settings.h"
#include "global.h"
#include "Lang.h"
#include "imgui/imgui.h"
#include "extension/Widgets.h"

SettingsUI settingsUI;

SettingsUI::SettingsUI() {
	// set all buffer to the values from Settings

	int killProofKey = settings.getKillProofKey();
	// copy in the string represantation of the key ID
	strcpy_s(shortcut, std::to_string(killProofKey).c_str());
	// convert virtual key to vsc key
	UINT vscKey = MapVirtualKeyA(killProofKey, MAPVK_VK_TO_VSC);
	// get the name representation of the key
	GetKeyNameTextA((vscKey << 16), shortCutRealName, 32);
}

void SettingsUI::draw() {
	// Setting to select, which key is used to open the killproofs menu (will also close it)
	ImGui::Text(lang.translate(LangKey::SettingsShortcutText).c_str());
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
		}
		catch ([[maybe_unused]] const std::invalid_argument& e) {

		}
		catch ([[maybe_unused]] const std::out_of_range& e) {

		}
	}
	ImGui::PopItemWidth();
	ImGui::SameLine();
	ImGui::TextUnformatted(shortCutRealName);

	ImGui::Checkbox(lang.translate(LangKey::SettingsDisableESCText).c_str(), &settings.settings.disableEscClose);
	if (ImGui::InputInt(lang.translate(LangKey::SettingsCofferValue).c_str(), &cofferValue)) {
		if (cofferValue < 0) {
			cofferValue = 0;
		}
		if (cofferValue > 5) {
			cofferValue = 5;
		}

		settings.settings.cofferValue = cofferValue;
	}

	ImGui::Checkbox(lang.translate(LangKey::SettingsHideExtrasMessage).c_str(), &settings.settings.hideExtrasMessage);

	if (ImGui::Button(lang.translate(LangKey::SettingsClearCacheText).c_str())) {
		std::scoped_lock<std::mutex, std::mutex> guard(cachedPlayersMutex, trackedPlayersMutex);

		// get all accountnames and charnames
		std::list<Player> usersToKeep;
		for (std::string trackedPlayer : trackedPlayers) {
			const Player& player = cachedPlayers.at(trackedPlayer);
			usersToKeep.emplace_back(player.username, player.addedBy, player.self, player.characterName, player.id);
		}

		// clear the cache
		cachedPlayers.clear();

		// refill the cache with only tracked players
		for (const Player& player : usersToKeep) {
			const auto& tryEmplace = cachedPlayers.try_emplace(player.username, player.username, player.addedBy, player.self, player.characterName, player.id);

			// load kp.me data if less than 10 people tracked
			loadKillproofsSizeChecked(tryEmplace.first->second);
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(lang.translate(LangKey::SettingsClearCacheTooltip).c_str());
}
