#include "SettingsUI.h"

#include <Windows.h>

#include "Player.h"
#include "Settings.h"
#include "global.h"
#include "Lang.h"
#include "imgui/imgui.h"
#include "extension/Widgets.h"

SettingsUI settingsUI;

void SettingsUI::draw() {
	if (initialized) {
		std::string killproofKey = std::to_string(settings.getKillProofKey());
		memset(shortcut, 0, sizeof(shortcut));
		killproofKey.copy(shortcut, killproofKey.size());

		cofferValue = settings.settings.cofferValue;

		initialized = true;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.f, 0.f});

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	ImGuiEx::KeyInput(lang.translate(LangKey::SettingsShortcutText).c_str(), "##shortcut", shortcut, sizeof(shortcut), settings.settings.killproofKey, lang.translate(LangKey::SettingsKeyNotSetText).c_str());

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

	ImGui::PopStyleVar();
}
