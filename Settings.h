#pragma once

#include <map>

#include "extension/arcdps_structs.h"
#include "json.hpp"
#include "Killproofs.h"
#include "imgui/imgui.h"

class WindowSettingsUI;
class SettingsUI;

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ImVec2, x, y)

class Settings {
	friend SettingsUI;
	friend WindowSettingsUI;

public:
	struct SettingsObject {
		int killproofKey;
		bool hidePrivateAccount;
		bool showKillproof;
		std::string blockedDataText;
		bool disableEscClose;
		Alignment alignment = Alignment::Left;
		bool showHeaderText;
		bool hideControls = false;
		bool showOverallByDefault = false;
		bool showHeader = true;
		Position position = Position::Manual;
		CornerPosition cornerPosition = CornerPosition::TopLeft;
		ImVec2 cornerVector;
		CornerPosition anchorPanelCornerPosition = CornerPosition::TopLeft;
		CornerPosition selfPanelCornerPosition = CornerPosition::TopLeft;
		ImGuiID fromWindowID;
		bool showCommander = false;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SettingsObject, killproofKey, hidePrivateAccount, showKillproof, blockedDataText, disableEscClose, alignment,
		                               showHeaderText, hideControls, showOverallByDefault, showHeader, position, cornerPosition, cornerVector,
		                               anchorPanelCornerPosition, selfPanelCornerPosition, fromWindowID)
	};

	Settings();
	~Settings();

	// getter/setter
	[[nodiscard]] int getKillProofKey() const;
	[[nodiscard]] bool getHidePrivateAccount() const;
	[[nodiscard]] bool& getShowKillproof();
	[[nodiscard]] const std::string& getBlockedDataText() const;
	[[nodiscard]] bool getDisableEscClose() const;
	[[nodiscard]] Alignment getAlignment() const;
	[[nodiscard]] bool getShowHeaderText() const;
	[[nodiscard]] bool getHideControls() const;
	[[nodiscard]] bool getShowOverallByDefault() const;
	[[nodiscard]] bool getShowHeader() const;
	[[nodiscard]] Position getPosition() const;
	[[nodiscard]] CornerPosition getCornerPosition() const;
	[[nodiscard]] const ImVec2& getCornerVector() const;
	[[nodiscard]] CornerPosition getAnchorPanelCornerPosition() const;
	[[nodiscard]] CornerPosition getSelfPanelCornerPosition() const;
	[[nodiscard]] ImGuiID getFromWindowID() const;
	[[nodiscard]] bool getShowCommander() const;

	// delete copy/move
	Settings(const Settings& other) = delete;
	Settings(Settings&& other) noexcept = delete;
	Settings& operator=(const Settings& other) = delete;
	Settings& operator=(Settings&& other) noexcept = delete;
private:
	void setDefaults();
	void saveToFile();
	void readFromFile();

	SettingsObject settings;
	bool visibilityPopup = true;
};

extern Settings settings;
