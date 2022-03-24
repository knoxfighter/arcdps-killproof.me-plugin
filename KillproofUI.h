#pragma once

#include "Player.h"

#include "extension/arcdps_structs.h"
#include "extension/Windows/MainWindow.h"
#include "extension/Singleton.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include <atomic>

typedef std::function<amountVal(const Killproof&)> kpFunction;

class KillproofUI : public MainWindow, public Singleton<KillproofUI> {
public:
	std::atomic_bool needSort = false;

	KillproofUI();
	bool& GetOpenVar() override;
	void SetMaxHeightCursorPos(float pNewCursorPos = ImGui::GetCursorPosY()) override;
	void Draw(ImGuiWindowFlags imGuiWindowFlags = 0, MainWindowFlags mainWindowFlags = 0) override {
		imGuiWindowFlags |= ImGuiWindowFlags_NoScrollbar;
		MainWindow::Draw(imGuiWindowFlags, mainWindowFlags);
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
	bool& getShowScrollbar() override;
	std::optional<ImVec2>& getPadding() override;
	bool getMaxHeightActive() override;

	void DrawContextMenu() override;
	void DrawStyleSettingsSubMenu() override;
	void DrawContent() override;

private:
	static void openInBrowser(const char* username);
	bool drawRow(const Alignment& alignment, const SYSTEMTIME* joinTime, const char* username, const char* characterName, const char* killproofId, const std::atomic<LoadingStatus>& status,
	             kpFunction killproofsFun, kpFunction coffersFun, kpFunction kpOverallFun, bool treeNode, bool isCommander);
	void drawTextColumn(bool* open, const char* text, const char* username, const std::atomic<LoadingStatus>& status, bool treeNode);
	void newRow();

	char userAddBuf[1024]{};
	ImGuiTable* table = nullptr;
	int mCurrentRow = 0;
	float mCurrentCursorPos = 0;
};
