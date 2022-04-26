#pragma once

#include "global.h"
#include "Lang.h"
#include "Killproofs.h"
#include "Player.h"

#include "extension/Icon.h"
#include "extension/Windows/MainTable.h"

using std::string_literals::operator ""s;

constexpr ImU32 JOIN_TIME_ID = 32;
constexpr ImU32 ACCOUNT_NAME_ID = 29;
constexpr ImU32 CHARACTER_NAME_ID = 30;
constexpr ImU32 KILLPROOF_ID_ID = 31;

static const std::vector<MainTableColumn> COLUMN_SETUP {
	{JOIN_TIME_ID, [] {return "#"s;}, []{return nullptr;}, "0", true},
	{ACCOUNT_NAME_ID, [] {return lang.translate(LangKey::Accountname);}, []{return nullptr;}, "0", true},
	{CHARACTER_NAME_ID, [] {return lang.translate(LangKey::Charactername);}, []{return nullptr;}, "0", true},
	{KILLPROOF_ID_ID, [] {return lang.translate(LangKey::KillproofId);}, []{return nullptr;}, "0", true},

	// Raids
	{0, [] {return to_string(Killproof::li);}, []{return iconLoader.getTexture(icons.at(Killproof::li));}, "1", true},
	{1, [] {return to_string(Killproof::ld);}, []{return iconLoader.getTexture(icons.at(Killproof::ld));}, "1", true},
	{2, [] {return to_string(Killproof::liLd);}, []{return iconLoader.getTexture(icons.at(Killproof::liLd));}, "1", true},

	// fractals
	{3, [] {return to_string(Killproof::uce);}, []{return iconLoader.getTexture(icons.at(Killproof::uce));}, "2", true},
	{4, [] {return to_string(Killproof::ufe);}, []{return iconLoader.getTexture(icons.at(Killproof::ufe));}, "2", true},

	// W1
	{5, [] {return to_string(Killproof::vg);}, []{return iconLoader.getTexture(icons.at(Killproof::vg));}, "1.1", false},
	{6, [] {return to_string(Killproof::gorse);}, []{return iconLoader.getTexture(icons.at(Killproof::gorse));}, "1.1", false},
	{7, [] {return to_string(Killproof::sabetha);}, []{return iconLoader.getTexture(icons.at(Killproof::sabetha));}, "1.1", false},

	// W2
	{8, [] {return to_string(Killproof::sloth);}, []{return iconLoader.getTexture(icons.at(Killproof::sloth));}, "1.2", false},
	{9, [] {return to_string(Killproof::matthias);}, []{return iconLoader.getTexture(icons.at(Killproof::matthias));}, "1.2", false},

	// W3
	{10, [] {return to_string(Killproof::escort);}, []{return iconLoader.getTexture(icons.at(Killproof::escort));}, "1.3", false},
	{11, [] {return to_string(Killproof::kc);}, []{return iconLoader.getTexture(icons.at(Killproof::kc));}, "1.3", false},
	{12, [] {return to_string(Killproof::xera);}, []{return iconLoader.getTexture(icons.at(Killproof::xera));}, "1.3", false},

	// W4
	{13, [] {return to_string(Killproof::cairn);}, []{return iconLoader.getTexture(icons.at(Killproof::cairn));}, "1.4", false},
	{14, [] {return to_string(Killproof::mo);}, []{return iconLoader.getTexture(icons.at(Killproof::mo));}, "1.4", false},
	{15, [] {return to_string(Killproof::samarog);}, []{return iconLoader.getTexture(icons.at(Killproof::samarog));}, "1.4", false},
	{16, [] {return to_string(Killproof::deimos);}, []{return iconLoader.getTexture(icons.at(Killproof::deimos));}, "1.4", false},

	// W5
	{17, [] {return to_string(Killproof::desmina);}, []{return iconLoader.getTexture(icons.at(Killproof::desmina));}, "1.5", false},
	{18, [] {return to_string(Killproof::river);}, []{return iconLoader.getTexture(icons.at(Killproof::river));}, "1.5", false},
	{19, [] {return to_string(Killproof::statues);}, []{return iconLoader.getTexture(icons.at(Killproof::statues));}, "1.5", false},
	{20, [] {return to_string(Killproof::dhuum);}, []{return iconLoader.getTexture(icons.at(Killproof::dhuum));}, "1.5", true},

	// W6
	{21, [] {return to_string(Killproof::ca);}, []{return iconLoader.getTexture(icons.at(Killproof::ca));}, "1.6", false},
	{22, [] {return to_string(Killproof::twins);}, []{return iconLoader.getTexture(icons.at(Killproof::twins));}, "1.6", false},
	{23, [] {return to_string(Killproof::qadim);}, []{return iconLoader.getTexture(icons.at(Killproof::qadim));}, "1.6", true},

	// W7
	{24, [] {return to_string(Killproof::sabir);}, []{return iconLoader.getTexture(icons.at(Killproof::sabir));}, "1.7", false},
	{25, [] {return to_string(Killproof::adina);}, []{return iconLoader.getTexture(icons.at(Killproof::adina));}, "1.7", false},
	{26, [] {return to_string(Killproof::qadim2);}, []{return iconLoader.getTexture(icons.at(Killproof::qadim2));}, "1.7", true},

	// Strikes
	{27, [] {return to_string(Killproof::boneskinnerVial);}, []{return iconLoader.getTexture(icons.at(Killproof::boneskinnerVial));}, "3", true},
};

class KillproofUITable : public MainTable<> {
public:
	KillproofUITable(MainWindow* pMainWindow, MainTableFlags pFlags)
		: MainTable<>(COLUMN_SETUP, pMainWindow, pFlags) {}

protected:
	void DrawRows(TableColumnIdx pFirstColumnIndex) override;
	void Sort(const ImGuiTableColumnSortSpecs* mColumnSortSpecs) override;

	Alignment& getAlignment() override;
	Alignment& getHeaderAlignment() override;
	std::string getTableId() override;
	int& getMaxDisplayed() override;
	bool& getShowAlternatingBackground() override;
	TableSettings& getTableSettings() override;
	bool& getHighlightHoveredRows() override;
	const char* getCategoryName(const std::string& pCat) override;

private:
	template<bool Linked = false>
	bool drawRow(TableColumnIdx pFirstColumnIndex, const Player& pPlayer, bool pHasLinked, bool pTotal = false, bool pTotalText = false);

	template<bool OpenBrowser = false>
	void drawTextColumn(bool& pOpen, const std::string& pText, const std::string& pUsername, const std::atomic<LoadingStatus>& pStatus, bool pTreeNode, bool pFirst, bool pIsCommander);

	void openInBrowser(const std::string& username);
};

