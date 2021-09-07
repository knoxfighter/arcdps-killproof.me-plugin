#include "Settings.h"

#include <fstream>

#include "global.h"

Settings settings;

int Settings::getKillProofKey() const {
	return settings.killproofKey;
}

bool Settings::getHidePrivateAccount() const {
	return settings.hidePrivateAccount;
}

bool& Settings::getShowKillproof() {
	return settings.showKillproof;
}

const std::string& Settings::getBlockedDataText() const {
	return settings.blockedDataText;
}

bool Settings::getDisableEscClose() const {
	return settings.disableEscClose;
}

Alignment Settings::getAlignment() const {
	return settings.alignment;
}

bool Settings::getShowHeaderText() const {
	return settings.showHeaderText;
	// return true;
}

bool Settings::getHideControls() const {
	return settings.hideControls;
}

bool Settings::getShowOverallByDefault() const {
	return settings.showOverallByDefault;
}

bool Settings::getShowHeader() const {
	return settings.showHeader;
}

Position Settings::getPosition() const {
	return settings.position;
}

CornerPosition Settings::getCornerPosition() const {
	return settings.cornerPosition;
}

const ImVec2& Settings::getCornerVector() const {
	return settings.cornerVector;
}

CornerPosition Settings::getAnchorPanelCornerPosition() const {
	return settings.anchorPanelCornerPosition;
}

CornerPosition Settings::getSelfPanelCornerPosition() const {
	return settings.selfPanelCornerPosition;
}

ImGuiID Settings::getFromWindowID() const {
	return settings.fromWindowID;
}

bool Settings::getShowCommander() const {
	return settings.showCommander;
}

uint8_t Settings::getCofferValue() const {
	return settings.cofferValue;
}

void Settings::load() {
	// according to standard, this constructor is completely thread-safe
	// read settings from file
	readFromFile();
}

void Settings::unload() {
	try {
		saveToFile();
	} catch (const std::exception& e) {
		// Some exception happened, i cannot do anything against it here :(
	}
}

void Settings::setDefaults() {
	// set defaults, they will be overriden, with what is saved in the file
	// set default key to "K"
	if (settings.killproofKey == 0) {
		settings.killproofKey = 0x4B;
	}

	if (settings.blockedDataText.empty()) {
		settings.blockedDataText = "-";
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
