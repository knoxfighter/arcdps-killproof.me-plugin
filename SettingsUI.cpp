#include "SettingsUI.h"

#include <Windows.h>

#include "Player.h"
#include "Settings.h"
#include "global.h"
#include "Lang.h"

#include "extension/KeyBindHandler.h"
#include "extension/KeyInput.h"

#include "imgui/imgui.h"
#include "extension/Widgets.h"

SettingsUI settingsUI;

void SettingsUI::Draw() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.f, 0.f});

	Settings& settings = Settings::instance();

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	KeyBinds::Modifier arcdpsModifier = KeyBindHandler::GetArcdpsModifier();
	KeyBinds::Key oldKey = settings.settings.windowKey;
	if (ImGuiEx::KeyCodeInput(lang.translate(LangKey::SettingsShortcutText).c_str(), settings.settings.windowKey,
	                          GlobalObjects::CURRENT_LANGUAGE, GlobalObjects::CURRENT_HKL,
	                          ImGuiEx::KeyCodeInputFlags_FixedModifier, arcdpsModifier)) {
		KeyBindHandler::instance().UpdateKeys(oldKey, settings.settings.windowKey);
	}

	ImGui::Checkbox(lang.translate(LangKey::SettingsDisableESCText).c_str(), &settings.settings.disableEscClose);
	int& cofferValue = settings.settings.cofferValue;
	if (ImGui::InputInt(lang.translate(LangKey::SettingsCofferValue).c_str(), &cofferValue)) {
		if (cofferValue < 0) {
			cofferValue = 0;
		}
		if (cofferValue > 5) {
			cofferValue = 5;
		}
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
			const auto& tryEmplace = cachedPlayers.try_emplace(player.username, player.username, player.addedBy,
			                                                   player.self, player.characterName, player.id);

			// load kp.me data if less than 10 people tracked
			loadKillproofsSizeChecked(tryEmplace.first->second);
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(lang.translate(LangKey::SettingsClearCacheTooltip).c_str());

	ImGui::PopStyleVar();
}
