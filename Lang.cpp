#include "Lang.h"

#include <fstream>
#include <iomanip>

#include "global.h"

Lang lang;

std::string Lang::translate(LangKey key) {
	return lang.translations.at(key);
}

Lang::Lang() {
	readFromFile();
}

Lang::~Lang() {
#if _DEBUG
	saveToFile();
#endif
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
	lang.translations.merge(defaults);
}
