#pragma once

#include <map>

#include "arcdps_structs.h"
#include "json.hpp"
#include "Killproofs.h"

class SettingsUI;

class Settings
{
    friend SettingsUI;

public:
    struct SettingsObject {
        int killproofKey;
        bool hidePrivateAccount;
        bool showKillproof;
        std::string blockedDataText;
        bool disableEscClose;
        Alignment alignment = Alignment::Left;
        bool showHeaderText;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsObject, killproofKey, hidePrivateAccount, showKillproof, blockedDataText, disableEscClose, alignment, showHeaderText)
    };

    static Settings& instance();

    // getter/setter
    [[nodiscard]] int getKillProofKey() const;
    [[nodiscard]] bool getHidePrivateAccount() const;
    [[nodiscard]] bool& getShowKillproof();
    [[nodiscard]] const std::string& getBlockedDataText() const;
    [[nodiscard]] bool getDisableEscClose() const;
    [[nodiscard]] Alignment getAlignment() const;
    [[nodiscard]] bool getShowHeaderText() const;

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
