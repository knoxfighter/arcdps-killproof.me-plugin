#pragma once

#include <map>

#include "Killproofs.h"

class SettingsUI;

class Settings
{
    friend SettingsUI;
	
public:
    static Settings& instance();

	// getter/setter
    [[nodiscard]] std::map<Killproof, bool> getActive() const;

private:
    // copy/move etc. will be deleted implicitly
    Settings();
    ~Settings();
    void saveToFile();
    void readFromFile();

    std::map<Killproof, bool> active;
};

