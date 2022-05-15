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

namespace {
	const std::map<LanguageSetting, std::function<const std::string&()>> PopupText = {
		{LanguageSetting::LikeGame, []() -> const std::string& { return Localization::STranslate(KMT_LanguageAsIngameTooltip); }},
		{LanguageSetting::German, []() -> const std::string& { return Localization::STranslate(KMT_LanguageGermanTooltip); }},
		{LanguageSetting::French, []() -> const std::string& { return Localization::STranslate(KMT_LanguageFrenchTooltip); }},
		{LanguageSetting::Spanish, []() -> const std::string& { return Localization::STranslate(KMT_LanguageSpanishTooltip); }},
	};
}

void SettingsUI::Draw() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.f, 0.f});

	Settings& settings = Settings::instance();

	
	if (ImGuiEx::EnumCombo(Localization::STranslate(ET_Language).c_str(), settings.settings.language, magic_enum::enum_values<LanguageSetting>(), PopupText)) {
		if (settings.settings.language == LanguageSetting::LikeGame) {
			Localization::SChangeLanguage(static_cast<gwlanguage>(GlobalObjects::CURRENT_LANGUAGE));
		} else {
			Localization::SChangeLanguage(static_cast<gwlanguage>(settings.settings.language));
		}
	}

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	KeyBinds::Modifier arcdpsModifier = KeyBindHandler::GetArcdpsModifier();
	KeyBinds::Key oldKey = settings.settings.windowKey;
	if (ImGuiEx::KeyCodeInput(Localization::STranslate(ET_Shortcut).c_str(), settings.settings.windowKey,
	                          GlobalObjects::CURRENT_LANGUAGE, GlobalObjects::CURRENT_HKL,
	                          ImGuiEx::KeyCodeInputFlags_FixedModifier, arcdpsModifier)) {
		KeyBindHandler::instance().UpdateKeys(oldKey, settings.settings.windowKey);
	}

	ImGui::Checkbox(Localization::STranslate(KMT_SettingsDisableESCText).c_str(), &settings.settings.disableEscClose);
	int& cofferValue = settings.settings.cofferValue;
	if (ImGui::InputInt(Localization::STranslate(KMT_SettingsCofferValue).c_str(), &cofferValue)) {
		if (cofferValue < 0) {
			cofferValue = 0;
		}
		if (cofferValue > 5) {
			cofferValue = 5;
		}
	}

	ImGui::Checkbox(Localization::STranslate(KMT_SettingsHideExtrasMessage).c_str(), &settings.settings.hideExtrasMessage);

	if (ImGui::Button(Localization::STranslate(KMT_SettingsClearCacheText).c_str())) {
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
		ImGui::SetTooltip(Localization::STranslate(KMT_SettingsClearCacheTooltip).c_str());

	ImGui::PopStyleVar();
}
