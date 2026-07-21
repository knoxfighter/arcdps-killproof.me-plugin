#include "Settings.h"

#include "global.h"

#include <ArcdpsUnofficialExtras/KeyBindHelper.h>
#include <fstream>

const std::string& Settings::GetLanguage() {
	if (settings.language2 == ::Lang::LikeGame) {
		return GlobalObjects::CURRENT_LANGUAGE;
	}
	return settings.language2;
}

void Settings::SetLanguage(std::string language) {
	settings.language2 = std::move(language);

	Localization::SChangeLanguage(GetLanguage());
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

			// get the object into the settings object
			json.get_to(settings);

			/**
			 * MIGRATIONS
			 */

			// set headerAlignment to normal alignment, when not found
			if (!json.contains("headerAlignment") && json.contains("alignment")) {
				settings.headerAlignment = json.at("alignment");
			}

			if (!json.contains("version")) {
				// no version set, do migration for v0 -> v1
				if (json.contains("hidePrivateAccount")) {
					const auto& hidePrivateAccounts = json.at("hidePrivateAccount");
					if (hidePrivateAccounts.is_boolean()) {
						settings.showPrivateAccounts = !hidePrivateAccounts.get<bool>();
					}
				}
				if (json.contains("hideControls")) {
					const auto& hideControls = json.at("hideControls");
					if (hideControls.is_boolean()) {
						settings.showControls = !hideControls.get<bool>();
					}
				}
				if (json.contains("showOverallByDefault")) {
					const auto& showOverallByDefault = json.at("showOverallByDefault");
					if (showOverallByDefault.is_boolean()) {
						settings.showLinkedByDefault = !showOverallByDefault.get<bool>();
					}
				}
				if (json.contains("killproofKey")) {
					const auto& killproofKey = json.at("killproofKey");
					if (killproofKey.is_number()) {
						WPARAM oldKey = killproofKey.get<WPARAM>();
						UINT vscKey = MapVirtualKeyA(oldKey, MAPVK_VK_TO_VSC);
						const auto& keyCode = KeyBinds::MsvcScanCodeToKeyCode(vscKey);
						if (keyCode) {
							settings.windowKey = SettingsKey(keyCode.value());
						}
					}
				}

				settings.version = 1;
			}

			if (settings.version == 1) {
				if (json.contains("language")) {
					const auto& languageField = json.at("language");
					if (languageField.is_number()) {
						auto languageNum = languageField.get<uint8_t>();
						switch (languageNum) {
						case 1:
							settings.language2 = ::Lang::LikeGame;
						default:
							settings.language2 = ArcdpsExtension::Localization::ToLangCode(static_cast<Language>(languageNum));
						}
					}
				}

				settings.version = 2;
			}

			// TODO: do further migrations here
		}
	} catch (const std::exception& e) {
		// some exception was thrown, all settings are reset!
		ARC_LOG(std::format("Error when reading settings: {}", e.what()).c_str());
		ARC_LOG_FILE(std::format("Error when reading settings: {}", e.what()).c_str());
	}
}
