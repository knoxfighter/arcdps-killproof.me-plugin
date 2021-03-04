#pragma once

#include <map>
#include <string>

#include "json.hpp"
#include "map.h"

#define BUILD_MAP(val, key) {key::val, #val}
#define LITERAL(val) val,
#define BUILD_ENUM_SERIALIZED(key, ...) \
	enum class key { \
		MAP(LITERAL, __VA_ARGS__) \
	}; \
	NLOHMANN_JSON_SERIALIZE_ENUM(key, { \
		MAP_LIST_UD( \
			BUILD_MAP, \
			key, \
			__VA_ARGS__ \
		) \
	})

BUILD_ENUM_SERIALIZED(
	LangKey,
	KpWindowName,
	SettingsWindowName,
	MenuName,
	SubMenuKp,
	SubMenuSettings,
	LI,
	Ld,
	LiLd,
	Uce,
	Ufe,
	Vg,
	Gorse,
	Sabetha,
	Sloth,
	Matthias,
	Escort,
	Kc,
	Xera,
	Cairn,
	Mo,
	Samarog,
	Deimos,
	Desmina,
	River,
	Statues,
	Dhuum,
	Ca,
	Twins,
	Qadim,
	Sabir,
	Adina,
	Qadim2,
	DefaultKp,
	Accountname,
	Charactername,
	CopyKpIdText,
	ClearText,
	ClearTooltip,
	AddPlayerTooltip,
	AddPlayerText,
	SettingsShortcutText,
	SettingsBlockedText,
	SettingsHidePrivateText,
	SettingsDisableESCText,
	SettingsShowHeaderText,
	Alignment,
	SettingsClearCacheText,
	SettingsClearCacheTooltip,
	Left,
	Center,
	Right
)

class Lang {
public:
	struct LangObject {
		std::map<LangKey, std::string> translations;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(LangObject, translations)
	};

	Lang();
	~Lang();

	std::string translate(LangKey key);

	// copy/move delete
	Lang(const Lang& other) = delete;
	Lang(Lang&& other) noexcept = delete;
	Lang& operator=(const Lang& other) = delete;
	Lang& operator=(Lang&& other) noexcept = delete;
	
private:
	void saveToFile();
	void readFromFile();
	void loadDefaults();

	LangObject lang;
};

extern Lang lang;
