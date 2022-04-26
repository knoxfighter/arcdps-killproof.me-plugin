#pragma once

#include <map>
#include <string>
#include <nlohmann/json.hpp>

#include "extension/map.h"

#define BUILD_MAP_JSON(val, val2, key) {key::val, #val}
#define BUILD_MAP_DEFAULTS(val1, val2, key) {key::val1, val2}
#define LITERAL(val1, val2) val1,
#define BUILD_ENUM_SERIALIZED(key, ...) \
	enum class key { \
		MAP2(LITERAL, __VA_ARGS__) \
	}; \
	NLOHMANN_JSON_SERIALIZE_ENUM(key, { \
		MAP_LIST_UD2( \
			BUILD_MAP_JSON, \
			key, \
			__VA_ARGS__ \
		) \
	}) \
	static std::map<LangKey, std::string> defaults = { \
		MAP_LIST_UD2( \
			BUILD_MAP_DEFAULTS, \
			key, \
			__VA_ARGS__ \
		) \
	};

BUILD_ENUM_SERIALIZED(
	LangKey,
	KpWindowName, "Killproof.me",
	MenuName, "Killproof.me",
	SubMenuKp, "Killproofs",
	SubMenuSettings, "Settings",
	LI, "LI",
	Ld, "LD",
	LiLd, "LI/LD",
	Uce, "UCE",
	Ufe, "UFE",
	Vg, "VG",
	Gorse, "Gorse",
	Sabetha, "Sabetha",
	Sloth, "Sloth",
	Matthias, "Matthias",
	Escort, "Escort",
	Kc, "KC",
	Xera, "Xera",
	Cairn, "Cairn",
	Mo, "MO",
	Samarog, "Samarog",
	Deimos, "Deimos",
	Desmina, "Desmina",
	River, "River",
	Statues, "Statues",
	Dhuum, "Dhuum",
	Ca, "CA",
	Twins, "Twins",
	Qadim, "Qadim",
	Sabir, "Sabir",
	Adina, "Adina",
	Qadim2, "Qadim2",
	BoneskinnerVial, "Boneskinner Ritual Vial",
	DefaultKp, "Unknown",
	Accountname, "Account",
	Charactername, "Character",
	KillproofId, "ID",
	CopyKpIdText, "Copy own KP ID",
	ClearText, "Clear",
	ClearTooltip, "Remove all manually added users",
	AddPlayerTooltip, "Accountname, killproof.me ID or Charactername to search and add to the list",
	AddPlayerText, "Add",
	Overall, "Overall",
	Killproofs, "Killproofs",
	Coffers, "Coffers",

	SettingsShortcutText, "Shortcut to open killproofs menu:",
	SettingsBlockedText, "Text to display when data is unavailable/private",
	SettingsShowPrivateText, "Private accounts",
	SettingsDisableESCText, "Do NOT close killproof.me window on ESC",
	SettingsShowHeaderText, "Show header with text instead of images",
	SettingsClearCacheText, "Clear Cache",
	SettingsClearCacheTooltip, "Clear the cache and reload killproof.me data for all players",
	SettingsShowControls, "Show controls (header buttons and search field)",
	SettingsShowLinkedByDefault, "Show linked account KPs by default",
	SettingsShowCommander, "Show commander Tag next to accountname",
	SettingsColumnSetup, "Column Setup",
	SettingsStyle, "Style",
	SettingsRaidsGroup, "Raids",
	SettingsRaidsW1Group, "W1",
	SettingsRaidsW2Group, "W2",
	SettingsRaidsW3Group, "W3",
	SettingsRaidsW4Group, "W4",
	SettingsRaidsW5Group, "W5",
	SettingsRaidsW6Group, "W6",
	SettingsRaidsW7Group, "W7",
	SettingsFractalsGroup, "Fractals",
	SettingsStrikesGruop, "Strikes",
	SettingsPosition, "Position",
	SettingsFromAnchorPanelCorner, "from anchor panel corner",
	SettingsToThisPanelCorner, "to this panel corner",
	SettingsFromWindowName, "from window",
	SettingsCofferValue, "Killproofs per coffer",
	SettingsHideExtrasMessage, "Hide Unofficial Extras Message",
	SettingsKeyNotSetText, "(not set)",

	Alignment, "Alignment",
	HeaderAlignment, "Header alignment",
	Language, "Language",
	Left, "Left",
	Center, "Center",
	Right, "Right",
	Unaligned, "",

	PositionManual, "manual",
	PositionScreenRelative, "screen relative position",
	PositionWindowRelative, "window relative position",

	CornerPositionTopLeft, "top-left",
	CornerPositionTopRight, "top-right",
	CornerPositionBottomLeft, "bottom-left",
	CornerPositionBottomRight, "bottom-right",

	SizingPolicySizeToContent, "Autoresize window to content",
	SizingPolicySizeContentToWindow, "Size content to window",
	SizingPolicyManualWindowSize, "Manual window sizing",

	UpdateWindowHeader, "Arcdps Killproof.me Plugin Update",
	UpdateDesc, "A new update for the Kilproof.me plugin is available.",
	UpdateCurrentVersion, "Current version",
	UpdateNewVersion, "New version",
	UpdateOpenPage, "Open download page",
	UpdateAutoButton, "Update automatically",
	UpdateInProgress, "Autoupdate in progress",
	UpdateRestartPending, "Autoupdate finished, restart your game to activate it.",
	UpdateError, "Autoupdate error, please update manually.",

	UnofficialExtrasNotInstalled, "Unofficial extras plugin is not installed.\nInstall it to enable tracking of players on other instances.",
	UnofficialExtrasInProgress, "Download in progress",
	UnofficialExtrasAutoButton, "Download automatically",
	UnofficialExtrasError, "Automatic installation failed, please install manually.",
	UnofficialExtrasRestartPending, "Installation complete, restart your game to activate it."
)

class Lang {
public:
	struct LangObject {
		std::map<LangKey, std::string> translations;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(LangObject, translations)
	};

	Lang() = default;
	~Lang() = default;

	const std::string& translate(LangKey key);

	void saveToFile();
	void readFromFile();

	// copy/move delete
	Lang(const Lang& other) = delete;
	Lang(Lang&& other) noexcept = delete;
	Lang& operator=(const Lang& other) = delete;
	Lang& operator=(Lang&& other) noexcept = delete;
	
private:
	void loadDefaults();

	LangObject lang;
};

extern Lang lang;
