#include "Settings.h"

#include <fstream>

Settings& Settings::instance() {
    static Settings b;
    return b;
}

kpActiveMap& Settings::getActive() {
    return settings.active;
}

int Settings::getKillProofKey() const {
	return settings.killproofKey;
}

void Settings::setKillProofKey(const int key) {
	settings.killproofKey = key;
}

Settings::~Settings() {
    saveToFile();
}

Settings::Settings() {
	// according to standard, this constructor is completely thread-safe
	// read settings from file
	readFromFile();
}

void Settings::setDefaults() {
	// set defaults, they will be overriden, with what is saved in the file
	// raid
	settings.active.try_emplace(Killproof::li, true);
	settings.active.try_emplace(Killproof::ld, true);
	settings.active.try_emplace(Killproof::liLd, false);
	// fractal
	settings.active.try_emplace(Killproof::ufe, true);
	settings.active.try_emplace(Killproof::uce, true);
	// w1
	settings.active.try_emplace(Killproof::vg, false);
	settings.active.try_emplace(Killproof::gorse, false);
	settings.active.try_emplace(Killproof::sabetha, false);
	// w2
	settings.active.try_emplace(Killproof::sloth, false);
	settings.active.try_emplace(Killproof::matthias, false);
	// w3
	settings.active.try_emplace(Killproof::escort, false);
	settings.active.try_emplace(Killproof::kc, false);
	settings.active.try_emplace(Killproof::xera, false);
	// w4
	settings.active.try_emplace(Killproof::cairn, false);
	settings.active.try_emplace(Killproof::mo, false);
	settings.active.try_emplace(Killproof::samarog, false);
	settings.active.try_emplace(Killproof::deimos, false);
	// w5
	settings.active.try_emplace(Killproof::desmina, false);
	settings.active.try_emplace(Killproof::river, false);
	settings.active.try_emplace(Killproof::statues, false);
	settings.active.try_emplace(Killproof::dhuum, true);
	// w6
	settings.active.try_emplace(Killproof::ca, false);
	settings.active.try_emplace(Killproof::twins, false);
	settings.active.try_emplace(Killproof::qadim, true);
	// w7
	settings.active.try_emplace(Killproof::adina, false);
	settings.active.try_emplace(Killproof::sabir, false);
	settings.active.try_emplace(Killproof::qadim2, true);

	// set default key to "K"
	if (settings.killproofKey == 0) {
		settings.killproofKey = 0x4B;
	}
}

void Settings::saveToFile() {
	// create json object
	auto json = nlohmann::json(settings);

	// open output file
	std::ofstream jsonFile("addons\\arcdps\\arcdps_killproof.me.json");

	// save json to file
	jsonFile << json;
}

void Settings::readFromFile() {
	try {
		// read a JSON file as stream
		std::ifstream jsonFile("addons\\arcdps\\arcdps_killproof.me.json");
		if (jsonFile.is_open()) {
			nlohmann::json json;

			// push stream into json object (this also parses it)
			jsonFile >> json;

			// get the objet into the settings object
			json.get_to(settings);
		}
	} catch (const std::exception& e) {
		// some exception was thrown, all settings are reset!
	}

	// merge in defaults, when not set
	setDefaults();
}
