#include "Settings.h"

#include <fstream>

Settings& Settings::instance() {
    static Settings b;
    return b;
}

std::map<Killproof, bool>& Settings::getActive() {
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
	// set defaults, they will be overriden, with what is saved in the file
	// raid
	settings.active[Killproof::li] = true;
	settings.active[Killproof::ld] = true;
	// fractal
	settings.active[Killproof::ufe] = true;
	settings.active[Killproof::uce] = true;
	// w1
	settings.active[Killproof::vg] = false;
	settings.active[Killproof::gorse] = false;
	settings.active[Killproof::sabetha] = false;
	// w2
	settings.active[Killproof::sloth] = false;
	settings.active[Killproof::matthias] = false;
	// w3
	settings.active[Killproof::escort] = false;
	settings.active[Killproof::kc] = false;
	settings.active[Killproof::xera] = false;
	// w4
	settings.active[Killproof::cairn] = false;
	settings.active[Killproof::mo] = false;
	settings.active[Killproof::samarog] = false;
	settings.active[Killproof::deimos] = false;
	// w5
	settings.active[Killproof::desmina] = false;
	settings.active[Killproof::river] = false;
	settings.active[Killproof::statues] = false;
	settings.active[Killproof::dhuum] = true;
	// w6
	settings.active[Killproof::ca] = false;
	settings.active[Killproof::twins] = false;
	settings.active[Killproof::qadim] = true;
	// w7
	settings.active[Killproof::adina] = false;
	settings.active[Killproof::sabir] = false;
	settings.active[Killproof::qadim2] = true;

	// set default key to "K"
	settings.killproofKey = 0x4B;
	
	// according to standard, this constructor is completely thread-safe
	// read settings from file
	readFromFile();
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
}
