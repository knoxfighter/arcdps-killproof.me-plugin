#include "SettingsUI.h"

#include "global.h"
#include "Lang.h"
#include "Player.h"
#include "Settings.h"

#include <ArcdpsExtension/KeyBindHandler.h>
#include <ArcdpsExtension/KeyInput.h>
#include <ArcdpsExtension/Widgets.h>
#include <imgui/imgui.h>

void SettingsUI::Draw() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {0.f, 0.f});

	Settings& settings = Settings::instance();
	auto& localization = Localization::instance();

	auto langLabel = std::format("{}###boontable_language", localization.Translate(ArcdpsExtension::ET_Language));
	auto langLabelPreview = settings.settings.language2 == ::Lang::LikeGame ? localization.Translate(ArcdpsExtension::ET_LikeInGame) : localization.Translate(settings.settings.language2, ArcdpsExtension::ET_LanguageName);
	if (ImGui::BeginCombo(langLabel.c_str(), langLabelPreview.data())) {
		for (auto& language : localization.GetLanguages()) {
			if (ImGui::Selectable(std::format("{}##{}", localization.Translate(language, ET_LanguageName), language).c_str(), language == settings.settings.language2)) {
				settings.SetLanguage(language);
			}
		}
		if (ImGui::Selectable(std::format("{}##{}", localization.Translate(ArcdpsExtension::ET_LikeInGame), ::Lang::LikeGame).c_str())) {
			settings.SetLanguage(::Lang::LikeGame);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("%s", Localization::STranslate(KMT_LanguageAsIngameTooltip).data());
		}

		ImGui::EndCombo();
	}

	// Setting to select, which key is used to open the killproofs menu (will also close it)
	KeyBinds::Modifier arcdpsModifier = KeyBindHandler::GetArcdpsModifier();
	KeyBinds::Key oldKey = settings.settings.windowKey;
	if (ImGuiEx::KeyCodeInput(Localization::STranslate(ET_Shortcut).data(), settings.settings.windowKey,GlobalObjects::CURRENT_HKL,
	                          ImGuiEx::KeyCodeInputFlags_FixedModifier, arcdpsModifier)) {
		KeyBindHandler::instance().UpdateKeys(oldKey, settings.settings.windowKey);
	}

	ImGui::Checkbox(Localization::STranslate(KMT_SettingsDisableESCText).data(), &settings.settings.disableEscClose);
	int& cofferValue = settings.settings.cofferValue;
	if (ImGui::InputInt(Localization::STranslate(KMT_SettingsCofferValue).data(), &cofferValue)) {
		cofferValue = std::clamp(cofferValue, 0, 5);
	}

	ImGui::Checkbox(Localization::STranslate(KMT_SettingsHideExtrasMessage).data(), &settings.settings.hideExtrasMessage);

	if (ImGui::Button(Localization::STranslate(KMT_SettingsClearCacheText).data())) {
		std::scoped_lock<std::mutex, std::mutex> guard(cachedPlayersMutex, trackedPlayersMutex);

		// get all accountnames and charnames
		std::list<Player> usersToKeep;
		for (const std::string& trackedPlayer : trackedPlayers) {
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
		ImGui::SetTooltip("%s", Localization::STranslate(KMT_SettingsClearCacheTooltip).data());

	ImGui::PopStyleVar();
}
