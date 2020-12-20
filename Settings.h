#pragma once

#include <map>

#include "json.hpp"
#include "Killproofs.h"

class SettingsUI;

typedef std::map<Killproof, bool, comparatorKillProof> kpActiveMap;

class Settings
{
    friend SettingsUI;

public:
    struct SettingsObject {
        kpActiveMap active;
        int killproofKey;
        bool hidePrivateAccount;
        bool hidePrivateData;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsObject, active, killproofKey, hidePrivateAccount, hidePrivateData)
    };

    static Settings& instance();

    // getter/setter
    [[nodiscard]] kpActiveMap& getActive();
    [[nodiscard]] int getKillProofKey() const;
    [[nodiscard]] bool getHidePrivateAccount() const;
    [[nodiscard]] bool getHidePrivateData() const;

private:
    // copy/move etc. will be deleted implicitly
    ~Settings();
    Settings();
    void setDefaults();
    void saveToFile();
    void readFromFile();

    SettingsObject settings;
    bool visibilityPopup = true;
};
