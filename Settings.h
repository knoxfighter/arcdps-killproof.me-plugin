#pragma once

#include "Killproofs.h"

#include "extension/arcdps_structs.h"
#include "extension/Singleton.h"
#include "extension/nlohmannJsonExtension.h"
#include "unofficial_extras/KeyBindStructs.h"

#include "imgui/imgui.h"

#include "unofficial_extras/Definitions.h"

#include <map>

#include <nlohmann/json.hpp>

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_NON_THROWING(ImVec2, x, y)

struct SettingsKey : KeyBinds::Key {
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsKey, DeviceType, Code, Modifier)
};

enum class LanguageSetting {
	English = 0,
	LikeGame = 1,
	French = 2,
	German = 3,
	Spanish = 4,
	// Chinese = 5
};
std::string to_string(LanguageSetting pLang);

class Settings : public Singleton<Settings> {
public:
	struct SettingsObject {
		uint32_t version = 1;
		SettingsKey windowKey {KeyBinds::DeviceType::Keyboard, static_cast<int32_t>(KeyBinds::KeyCode::K), 0};
		bool showPrivateAccounts = true;
		bool showKillproof = false;
		std::string blockedDataText;
		bool disableEscClose = false;
		Alignment alignment = Alignment::Left;
		Alignment headerAlignment = Alignment::Left;
		bool showControls = true;
		bool showLinkedByDefault = false;
		bool showHeaderText = false; // this is for the header in the table
		bool showHeader = true;
		bool showBackground = true;
		bool showScrollbar = true;
		Position position = Position::Manual;
		CornerPosition cornerPosition = CornerPosition::TopLeft;
		ImVec2 cornerVector;
		CornerPosition anchorPanelCornerPosition = CornerPosition::TopLeft;
		CornerPosition selfPanelCornerPosition = CornerPosition::TopLeft;
		ImGuiID fromWindowID = 0;
		bool showCommander = false;
		int cofferValue = 3;
		bool hideExtrasMessage = false;
		SizingPolicy sizingPolicy = SizingPolicy::SizeToContent;
		std::optional<std::string> headerText;
		std::optional<std::string> appearAsInOption;
		std::optional<ImVec2> windowPadding;
		int maxDisplayed = 0;
		LanguageSetting language = LanguageSetting::LikeGame;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_NON_THROWING(SettingsObject, version, windowKey, showPrivateAccounts, showKillproof,
		                                            blockedDataText, disableEscClose,
		                                            alignment, headerAlignment, showControls,
		                                            showLinkedByDefault, showHeader, position,
		                                            cornerPosition, cornerVector, anchorPanelCornerPosition,
		                                            selfPanelCornerPosition, fromWindowID,
		                                            showCommander, cofferValue, hideExtrasMessage, sizingPolicy,
		                                            headerText, appearAsInOption, showBackground, showScrollbar,
		                                            windowPadding, maxDisplayed, language)
	};

	Settings() = default;

	void load();
	void unload();

	SettingsObject settings;

	[[nodiscard]] Language GetLanguage();

	// delete copy/move
	Settings(const Settings& other) = delete;
	Settings(Settings&& other) noexcept = delete;
	Settings& operator=(const Settings& other) = delete;
	Settings& operator=(Settings&& other) noexcept = delete;
private:
	void saveToFile();
	void readFromFile();
};
