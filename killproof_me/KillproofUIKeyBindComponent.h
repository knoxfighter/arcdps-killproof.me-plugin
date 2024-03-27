#pragma once

#include "global.h"
#include "Settings.h"

#include "ArcdpsExtension/Windows/KeyBindComponent.h"

class KillproofUIKeyBindComponent : public KeyBindComponent {
public:
	explicit KillproofUIKeyBindComponent(MainWindow* pMainWindow)
		: KeyBindComponent(pMainWindow) {}

protected:
	KeyBinds::Key& getKeyBind() override;
	HKL getCurrentHKL() override;
	gwlanguage getCurrentLanguage() override;
	bool getKeyBindSwitch() override;
	bool getCloseWithEsc() override;
	bool getCloseWithEscActive() override;
};
