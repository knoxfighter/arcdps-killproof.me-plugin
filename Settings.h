#pragma once

#include <map>

#include "json.hpp"
#include "Killproofs.h"

class SettingsUI;

class Settings
{
    friend SettingsUI;
	
public:
    struct SettingsObject {
        std::map<Killproof, bool> active;
        int killproofKey;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsObject, active, killproofKey)
    };

    static Settings& instance();

	// getter/setter
    [[nodiscard]] std::map<Killproof, bool>& getActive();
    [[nodiscard]] int getKillProofKey() const;
    void setKillProofKey(int key);

private:
    // copy/move etc. will be deleted implicitly
    Settings();
    ~Settings();
    void saveToFile();
    void readFromFile();

    SettingsObject settings;
    bool visibilityPopup = true;
};
