#include "Lang.h"

#include <fstream>
#include <iomanip>

Lang& Lang::instance() {
	static Lang i;
	return i;
}

std::string Lang::translate(LangKey key) {
	return instance().lang.translations.at(key);
}

Lang::Lang() {
	readFromFile();
}

Lang::~Lang() {
	saveToFile();
}

void Lang::saveToFile() {
	// create json object
	auto json = nlohmann::json(lang);

	// open output file
	std::ofstream jsonFile("addons\\arcdps\\arcdps_lang_killproof.me.json");

	// save json to file
	jsonFile << std::setw(4) << json;
}

void Lang::readFromFile() {
	try {
		// read a JSON file as stream
		std::ifstream jsonFile("addons\\arcdps\\arcdps_lang_killproof.me.json");
		if (jsonFile.is_open()) {
			nlohmann::json json;

			// push stream into json object (this also parses it)
			jsonFile >> json;

			// get the objet into the settings object
			json.get_to(lang);
		}
	} catch (const std::exception& e) {
		// some exception was thrown, all settings are reset!
	}

	// merge in the defaults
	loadDefaults();
}

void Lang::loadDefaults() {
	std::map<LangKey, std::string> defaults = {
		{LangKey::KpWindowName, "Killproof.me"},
		{LangKey::SettingsWindowName, "Killproof.me Settings"},
		{LangKey::MenuName, "Killproof.me"},
		{LangKey::SubMenuKp, "Killproofs"},
		{LangKey::SubMenuSettings, "Settings"},
		{LangKey::LI, "LI"},
		{LangKey::Ld, "LD"},
		{LangKey::LiLd, "LI/LD"},
		{LangKey::Uce, "UCE"},
		{LangKey::Ufe, "UFE"},
		{LangKey::Vg, "VG"},
		{LangKey::Gorse, "Gorse"},
		{LangKey::Sabetha, "Sabetha"},
		{LangKey::Sloth, "Sloth"},
		{LangKey::Matthias, "Matthias"},
		{LangKey::Escort, "Escort"},
		{LangKey::Kc, "KC"},
		{LangKey::Xera, "Xera"},
		{LangKey::Cairn, "Cairn"},
		{LangKey::Mo, "MO"},
		{LangKey::Samarog, "Samarog"},
		{LangKey::Deimos, "Deimos"},
		{LangKey::Desmina, "Desmina"},
		{LangKey::River, "River"},
		{LangKey::Statues, "Statues"},
		{LangKey::Dhuum, "Dhuum"},
		{LangKey::Ca, "CA"},
		{LangKey::Twins, "Twins"},
		{LangKey::Qadim, "Qadim"},
		{LangKey::Sabir, "Sabir"},
		{LangKey::Adina, "Adina"},
		{LangKey::Qadim2, "Qadim2"},
		{LangKey::DefaultKp, "Unknown"},
		{LangKey::Accountname, "Accountname"},
		{LangKey::Charactername, "Charactername"},
		{LangKey::CopyKpIdText, "Copy own KP ID"},
		{LangKey::ClearText, "Clear"},
		{LangKey::ClearTooltip, "Remove all manually added users"},
		{LangKey::AddPlayerTooltip, "Accountname, killproof.me ID or Charactername to search and add to the list"},
		{LangKey::AddPlayerText, "Add"},
		{LangKey::SettingsShortcutText, "Shortcut to open killproofs menu:"},
		{LangKey::SettingsBlockedText, "Text to display when data is unavailable/private"},
		{LangKey::SettingsHidePrivateText, "Hide players without killproof.me account"},
		{LangKey::SettingsDisableESCText, "Do NOT close killproof.me window on ESC"},
		{LangKey::SettingsShowHeaderText, "Show header with text instead of images"},
		{LangKey::Alignment, "Alignment"},
		{LangKey::SettingsClearCacheText, "Clear cache"},
		{LangKey::SettingsClearCacheTooltip, "Clear the cache and reload killproof.me data for all players"},
		{LangKey::Left, "Left"},
		{LangKey::Center, "Center"},
		{LangKey::Right, "Right"},
	};
	lang.translations.merge(defaults);
}
