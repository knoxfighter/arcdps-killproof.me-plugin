#include "KillproofUI.h"

#include "global.h"
#include "KillproofUIPositioningComponent.h"
#include "KillproofUIKeyBindComponent.h"
#include "Lang.h"
#include "Player.h"
#include "Settings.h"

#include "extension/ExtensionTranslations.h"
#include "extension/IconLoader.h"
#include "extension/imgui_stdlib.h"
#include "extension/Localization.h"
#include "extension/Widgets.h"

#include <future>
#include <mutex>
#include <Windows.h>

using std::string_literals::operator ""s;

KillproofUI::KillproofUI() {
	CreateComponent<KillproofUIPositioningComponent>();
	CreateComponent<KillproofUIKeyBindComponent>();

	mTable = std::make_unique<KillproofUITable>(this, MainTableFlags_SubWindow);
}

bool& KillproofUI::GetOpenVar() {
	return Settings::instance().settings.showKillproof;
}

SizingPolicy& KillproofUI::getSizingPolicy() {
	return Settings::instance().settings.sizingPolicy;
}

bool& KillproofUI::getShowTitleBar() {
	return Settings::instance().settings.showHeader;
}

std::optional<std::string>& KillproofUI::getTitle() {
	return Settings::instance().settings.headerText;
}

const std::string& KillproofUI::getTitleDefault() {
	return Localization::STranslate(KMT_KpWindowNameDefault);
}

const std::string& KillproofUI::getWindowID() {
	return "Killproof.me"s;
}

std::optional<std::string>& KillproofUI::getAppearAsInOption() {
	return Settings::instance().settings.appearAsInOption;
}

const std::string& KillproofUI::getAppearAsInOptionDefault() {
	return Localization::STranslate(KMT_AppearAsInOptionDefault);
}

bool& KillproofUI::getShowBackground() {
	return Settings::instance().settings.showBackground;
}

bool& KillproofUI::GetShowScrollbar() {
	return Settings::instance().settings.showScrollbar;
}

std::optional<ImVec2>& KillproofUI::getPadding() {
	return Settings::instance().settings.windowPadding;
}

void KillproofUI::DrawContextMenu() {
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

	mTable->DrawColumnSetupMenu();

	ImGui::PopStyleVar();
}

void KillproofUI::DrawStyleSettingsSubMenu() {
	Settings& settings = Settings::instance();
	ImGui::Checkbox(Localization::STranslate(KMT_SettingsShowPrivateText).c_str(), &settings.settings.showPrivateAccounts);
	ImGui::Checkbox(Localization::STranslate(KMT_SettingsShowControls).c_str(), &settings.settings.showControls);
	ImGui::Checkbox(Localization::STranslate(KMT_SettingsShowLinkedByDefault).c_str(), &settings.settings.showLinkedByDefault);
	ImGui::Checkbox(Localization::STranslate(KMT_SettingsShowCommander).c_str(), &settings.settings.showCommander);
	if (ImGui::Checkbox(Localization::STranslate(KMT_ShowLinkedTotals).c_str(), &Settings::instance().settings.showLinkedTotalsOnUser)) {
		// trigger resort when this option is changed
		mTable->RequestSort();
	}

	// input for data private
	ImGui::PushItemWidth(50);
	ImGui::InputText(Localization::STranslate(KMT_SettingsBlockedText).c_str(), &settings.settings.blockedDataText);
	ImGui::PopItemWidth();

	ImGui::Separator();

	MainWindow::DrawStyleSettingsSubMenu();
}

void KillproofUI::DrawContent() {
	// lock the mutexes, before we access sensible data
	std::scoped_lock<std::mutex, std::mutex> lock(trackedPlayersMutex, cachedPlayersMutex);

	auto& settings = Settings::instance();

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
	 * Unofficial Extras message
	 */
	if (!extrasLoaded && !settings.settings.hideExtrasMessage) {
		ImGui::TextUnformatted(Localization::STranslate(KMT_UnofficialExtrasNotInstalled).c_str());

		ImGui::SameLine();
		if (ImGui::Button(Localization::STranslate(ET_UpdateOpenPage).c_str())) {
			std::thread([] {
				ShellExecuteA(nullptr, nullptr, "https://github.com/Krappa322/arcdps_unofficial_extras_releases/releases/latest", nullptr, nullptr, SW_SHOW);
			}).detach();
		}

		ImGui::SameLine();
		if (ImGui::Button("X")) {
			extrasLoaded = true;
		}
	}

	/**
	* Controls
	*/
	if (settings.settings.showControls) {
		bool addPlayer = false;
		if (ImGui::InputText("##useradd", userAddBuf, sizeof userAddBuf, ImGuiInputTextFlags_EnterReturnsTrue)) {
			addPlayer = true;
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(Localization::STranslate(KMT_AddPlayerTooltip).c_str());
		ImGui::SameLine();
		if (ImGui::Button(Localization::STranslate(KMT_AddPlayerText).c_str())) {
			addPlayer = true;
		}

		if (addPlayer) {
			std::string username(userAddBuf);

			// only run when username is not empty
			if (!username.empty()) {
				const auto& existingPlayer = std::ranges::find_if(cachedPlayers, [&username](const auto& elem) -> bool {
					return elem.first == username || elem.second.characterName == username || elem.second.killproofId == username;
				});

				if (existingPlayer == cachedPlayers.end()) {
					// add new player
					trackedPlayers.emplace_back(username);

					const auto& tryEmplace = cachedPlayers.try_emplace(username, username, AddedBy::Manually);
					// This should always be `true`
					if (tryEmplace.second) {
						loadKillproofs(tryEmplace.first->second);
					}
				} else {
					// player already exists
					// update username to actual accountname
					username = existingPlayer->first;
					
					// check of player is already tracked
					if (std::ranges::find(trackedPlayers, username) == trackedPlayers.end()) {
						// not yet tracked, add to tracking and update
						trackedPlayers.emplace_back(username);

						// set to Manually added
						existingPlayer->second.addedBy = AddedBy::Manually;
						existingPlayer->second.resetJoinedTime();
						loadKillproofs(existingPlayer->second);
					} else {
						// user already exists and user is already tracked -> Try to load killproofs to override sizeCheck
						loadKillproofs(existingPlayer->second);
					}
				}
				userAddBuf[0] = '\0';
			}
		}

		ImGui::SameLine();
		if (ImGui::Button(Localization::STranslate(KMT_ClearText).c_str())) {
			trackedPlayers = instancePlayers;
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip(Localization::STranslate(KMT_ClearTooltip).c_str());
		}

		// get own player
		const auto& playerIt = cachedPlayers.find(selfAccountName);
		if (playerIt != cachedPlayers.end()) {
			const Player& player = playerIt->second;
			if (player.status == LoadingStatus::Loaded) {
				ImGui::SameLine();

				if (ImGui::Button(Localization::STranslate(KMT_CopyKpIdText).c_str())) {
					// create string to copy
					std::string str;
					str.append("Killproof.me: ");
					str.append(player.killproofId);

					// copy ID to clipboard
					//put your text in source
					if (OpenClipboard(NULL)) {
						HGLOBAL clipbuffer;
						char* buffer;
						EmptyClipboard();
						clipbuffer = GlobalAlloc(GMEM_DDESHARE, str.size() + 1);
						buffer = (char*)GlobalLock(clipbuffer);
						memset(buffer, 0, str.size() + 1);
						str.copy(buffer, str.size());
						GlobalUnlock(clipbuffer);
						SetClipboardData(CF_TEXT, clipbuffer);
						CloseClipboard();
					}
				}
			}
		}
	}

	/**
	* TABLE
	*/
	mTable->Draw();
}
