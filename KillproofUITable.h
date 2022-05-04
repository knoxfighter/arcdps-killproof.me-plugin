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
constexpr ImU32 SUBGROUP_ID = 64;

static const std::vector<MainTableColumn> COLUMN_SETUP {
	// general stuff
	{JOIN_TIME_ID, [] {return "#"s;}, []{return nullptr;}, "0", true},
	{ACCOUNT_NAME_ID, [] {return lang.translate(LangKey::Accountname);}, []{return nullptr;}, "0", true},
	{CHARACTER_NAME_ID, [] {return lang.translate(LangKey::Charactername);}, []{return nullptr;}, "0", true},
	{KILLPROOF_ID_ID, [] {return lang.translate(LangKey::KillproofId);}, []{return nullptr;}, "0", true},
	{SUBGROUP_ID, [] {return lang.translate(LangKey::SubgroupText);}, []{return nullptr;}, "0", false},

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
	
	// EOD strikes
	{35, [] {return to_string(Killproof::maiTrin);}, []{return iconLoader.getTexture(icons.at(Killproof::maiTrin));}, "3", false},
	{33, [] {return to_string(Killproof::ankka);}, []{return iconLoader.getTexture(icons.at(Killproof::ankka));}, "3", false},
	{37, [] {return to_string(Killproof::ministerLi);}, []{return iconLoader.getTexture(icons.at(Killproof::ministerLi));}, "3", false},
	{34, [] {return to_string(Killproof::harvest);}, []{return iconLoader.getTexture(icons.at(Killproof::harvest));}, "3", false},
	{36, [] {return to_string(Killproof::maiTrinCM);}, []{return iconLoader.getTexture(icons.at(Killproof::maiTrinCM));}, "3", false},
};

// Key is the mapId found in the mumbleLink
// Value is a vector of columns that should be shown for that map. The Values are the UserIds from the ColumnSetup.
// TODO: update this when the above vector changes!
static const std::unordered_map<uint32_t, std::vector<size_t>> mapIdToColumnSetup = {
	{1155, {0, 1, 2, 20, 23, 26}}, // Aerodrome
	{1062, {0, 1, 2, 5, 6, 7}}, // W1
	{1149, {0, 1, 2, 8, 9}}, // W2
	{1156, {0, 1, 2, 10, 11, 12}}, // W3
	{1188, {0, 1, 2, 13, 14, 15, 16}}, // W4
	{1264, {0, 1, 2, 17, 18, 19, 20}}, // W5
	{1303, {0, 1, 2, 21, 22, 23}}, // W6
	{1323, {0, 1, 2, 24, 25, 26}}, // W7
	{1370, {0, 1, 2, 27}}, // Eye of the north
	{1432, {0, 1, 2, 35, 36}}, // MaiTrin strike
	{1451, {0, 1, 2, 37}}, // MinisterLi strike
	{1437, {0, 1, 2, 34}}, // HarvestTemple strike
	{1428, {0, 1, 2, 33, 34, 35, 36, 37}}, // Arborstone
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
	void MigrateSettings() override;
	bool getCustomColumnsFeatureActive() override { return true; }
	bool& getCustomColumnsActive() override;
	int getCustomColumnsFirstColumn() override { return 5; }

private:
	template<bool Linked = false>
	bool drawRow(TableColumnIdx pFirstColumnIndex, const Player& pPlayer, bool pHasLinked, bool pTotal = false, bool pTotalText = false);

	template<bool OpenBrowser = false>
	void drawTextColumn(bool& pOpen, const std::string& pText, const std::string& pUsername, const std::atomic<LoadingStatus>& pStatus, bool pTreeNode, bool pFirst, bool pIsCommander);

	void openInBrowser(const std::string& username);
};
