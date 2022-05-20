#pragma once

#include "KillproofUITable.h"
#include "Player.h"

#include "extension/arcdps_structs.h"
#include "extension/Windows/MainWindow.h"
#include "extension/Singleton.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

typedef std::function<amountVal(const Killproof&)> kpFunction;

class KillproofUI final : public MainWindow, public Singleton<KillproofUI> {
public:
	KillproofUI();
	bool& GetOpenVar() override;
	void Draw(ImGuiWindowFlags imGuiWindowFlags = 0, MainWindowFlags mainWindowFlags = 0) override {
		imGuiWindowFlags |= ImGuiWindowFlags_NoScrollbar;
		MainWindow::Draw(imGuiWindowFlags, mainWindowFlags);
	}
	const auto& GetTable() {
		return mTable;
	}

protected:
	SizingPolicy& getSizingPolicy() override;
	bool& getShowTitleBar() override;
	std::optional<std::string>& getTitle() override;
	const std::string& getTitleDefault() override;
	const std::string& getWindowID() override;
	std::optional<std::string>& getAppearAsInOption() override;
	const std::string& getAppearAsInOptionDefault() override;
	bool& getShowBackground() override;
	bool& GetShowScrollbar() override;
	std::optional<ImVec2>& getPadding() override;

	void DrawContextMenu() override;
	void DrawStyleSettingsSubMenu() override;
	void DrawContent() override;

private:
	char userAddBuf[1024]{};
	std::unique_ptr<KillproofUITable> mTable;
};
