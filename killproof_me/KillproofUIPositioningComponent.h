#pragma once

#include "Settings.h"

#include "extension/Windows/PositioningComponent.h"

class KillproofUIPositioningComponent final : public PositioningComponent {
public:
	explicit KillproofUIPositioningComponent(MainWindow* pMainWindow)
		: PositioningComponent(pMainWindow) {}

protected:
	Position& getPositionMode() override {
		return Settings::instance().settings.position;
	}
	CornerPosition& getCornerPosition() override {
		return Settings::instance().settings.cornerPosition;
	}
	ImVec2& getCornerVector() override {
		return Settings::instance().settings.cornerVector;
	}
	CornerPosition& getAnchorPanelCorner() override {
		return Settings::instance().settings.anchorPanelCornerPosition;
	}
	CornerPosition& getSelfPanelCorner() override {
		return Settings::instance().settings.selfPanelCornerPosition;
	}
	ImGuiID& getFromWindowId() override {
		return Settings::instance().settings.fromWindowID;
	}
};
