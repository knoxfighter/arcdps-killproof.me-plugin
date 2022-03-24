#include "KillproofUIKeyBindComponent.h"

KeyBinds::Key& KillproofUIKeyBindComponent::getKeyBind() {
	return Settings::instance().settings.windowKey;
}

HKL KillproofUIKeyBindComponent::getCurrentHKL() {
	return GlobalObjects::CURRENT_HKL;
}

gwlanguage KillproofUIKeyBindComponent::getCurrentLanguage() {
	return static_cast<gwlanguage>(Settings::instance().GetLanguage());
}

bool KillproofUIKeyBindComponent::getKeyBindSwitch() {
	GlobalObjects::UpdateArcExports();
	return !GlobalObjects::ARC_HIDE_ALL;
}

bool KillproofUIKeyBindComponent::getCloseWithEsc() {
	GlobalObjects::UpdateArcExports();
	return !Settings::instance().settings.disableEscClose && GlobalObjects::ARC_WINDOW_FASTCLOSE;
}

bool KillproofUIKeyBindComponent::getCloseWithEscActive() {
	return true;
}
