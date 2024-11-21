#pragma once

#include "global.h"
#include "Icons.h"
#include "Lang.h"
#include "Killproofs.h"
#include "Player.h"
#include "resource.h"

#include "ArcdpsExtension/IconLoader.h"
#include "ArcdpsExtension/Windows/MainTable.h"

using namespace ArcdpsExtension;
using std::string_literals::operator ""s;

constexpr ImU32 JOIN_TIME_ID = 32;
constexpr ImU32 ACCOUNT_NAME_ID = 29;
constexpr ImU32 CHARACTER_NAME_ID = 30;
constexpr ImU32 KILLPROOF_ID_ID = 31;
constexpr ImU32 SUBGROUP_ID = 64;

static std::optional<size_t> UCE_TEXTURE;
static std::optional<size_t> MAI_TRIN_TEXTURE;
static std::optional<size_t> ANKKA_TEXTURE;
static std::optional<size_t> LI_TEXTURE;
static std::optional<size_t> HARVEST_TEXTURE;
static std::optional<size_t> OLC_TEXTURE;
static std::optional<size_t> DAGDA_TEXTURE;
static std::optional<size_t> CERUS_TEXTURE;

static void* draw_texture(KillproofIcons id) {
	return IconLoader::instance().Draw(id);
}

// the index is used for the order 
static const std::vector<MainTableColumn> COLUMN_SETUP {
	// general stuff
	{JOIN_TIME_ID, [] {return "#"s;}, []{return nullptr;}, "0", true},
	{ACCOUNT_NAME_ID, [] {return Localization::STranslate(KMT_AccountName);}, []{return nullptr;}, "0", true},
	{CHARACTER_NAME_ID, [] {return Localization::STranslate(KMT_CharacterName);}, []{return nullptr;}, "0", true},
	{KILLPROOF_ID_ID, [] {return Localization::STranslate(KMT_KillproofId);}, []{return nullptr;}, "0", true},
	{SUBGROUP_ID, [] {return Localization::STranslate(KMT_SubgroupText);}, []{return nullptr;}, "0", false},

	// Raids
	// {0, [] {return to_string_short(Killproof::li);}, []{ return GET_TEXTURE(LI, ID_LI); }, "1", true},
	// {1, [] {return to_string_short(Killproof::ld);}, []{ return GET_TEXTURE(LD, ID_LD); }, "1", true},
	{2, [] {return to_string_short(Killproof::liLd);}, []{ return draw_texture(KillproofIcons::LI); }, "1", true},

	// fractals
	{3, [] {return to_string_short(Killproof::uce);}, []{ return draw_texture(KillproofIcons::UFE); }, "2", true},
	{4, [] {return to_string_short(Killproof::ufe);}, []{ return draw_texture(KillproofIcons::UFE); }, "2", true},

	// W1
	{5, [] {return to_string_short(Killproof::vg);}, []{ return draw_texture(KillproofIcons::VG); }, "1.1", [] {return to_string_long(Killproof::vg);}, false},
	{6, [] {return to_string_short(Killproof::gorse);}, []{ return draw_texture(KillproofIcons::Gorse); }, "1.1", [] {return to_string_long(Killproof::gorse);}, false},
	{7, [] {return to_string_short(Killproof::sabetha);}, []{ return draw_texture(KillproofIcons::Sabetha); }, "1.1", [] {return to_string_long(Killproof::sabetha);}, false},

	// W2
	{8, [] {return to_string_short(Killproof::sloth);}, []{ return draw_texture(KillproofIcons::Sloth); }, "1.2", false},
	{9, [] {return to_string_short(Killproof::matthias);}, []{ return draw_texture(KillproofIcons::Matt); }, "1.2", [] {return to_string_long(Killproof::matthias);}, false},

	// W3
	{10, [] {return to_string_short(Killproof::escort);}, []{ return draw_texture(KillproofIcons::Escort); }, "1.3", false},
	{11, [] {return to_string_short(Killproof::kc);}, []{ return draw_texture(KillproofIcons::KC); }, "1.3", [] {return to_string_long(Killproof::kc);}, false},
	{12, [] {return to_string_short(Killproof::xera);}, []{ return draw_texture(KillproofIcons::Xera); }, "1.3", false},

	// W4
	{13, [] {return to_string_short(Killproof::cairn);}, []{ return draw_texture(KillproofIcons::Cairn); }, "1.4", [] {return to_string_long(Killproof::cairn);}, false},
	{14, [] {return to_string_short(Killproof::mo);}, []{ return draw_texture(KillproofIcons::MO); }, "1.4", [] {return to_string_long(Killproof::mo);}, false},
	{15, [] {return to_string_short(Killproof::samarog);}, []{ return draw_texture(KillproofIcons::Samarog); }, "1.4", false},
	{16, [] {return to_string_short(Killproof::deimos);}, []{ return draw_texture(KillproofIcons::Deimos); }, "1.4", false},

	// W5
	{17, [] {return to_string_short(Killproof::desmina);}, []{ return draw_texture(KillproofIcons::Desmina); }, "1.5", [] {return to_string_long(Killproof::desmina);}, false},
	{18, [] {return to_string_short(Killproof::river);}, []{ return draw_texture(KillproofIcons::River); }, "1.5", [] {return to_string_long(Killproof::river);}, false},
	{19, [] {return to_string_short(Killproof::statues);}, []{ return draw_texture(KillproofIcons::Statues); }, "1.5", false},
	{20, [] {return to_string_short(Killproof::dhuum);}, []{ return draw_texture(KillproofIcons::Dhuum); }, "1.5", true},

	// W6
	{21, [] {return to_string_short(Killproof::ca);}, []{ return draw_texture(KillproofIcons::CA); }, "1.6", [] {return to_string_long(Killproof::ca);}, false},
	{22, [] {return to_string_short(Killproof::twins);}, []{ return draw_texture(KillproofIcons::Twins); }, "1.6", [] {return to_string_long(Killproof::twins);}, false},
	{23, [] {return to_string_short(Killproof::qadim);}, []{ return draw_texture(KillproofIcons::Qadim1); }, "1.6", true},

	// W7
	{24, [] {return to_string_short(Killproof::sabir);}, []{ return draw_texture(KillproofIcons::Sabir); }, "1.7", false},
	{25, [] {return to_string_short(Killproof::adina);}, []{ return draw_texture(KillproofIcons::Adina); }, "1.7", false},
	{26, [] {return to_string_short(Killproof::qadim2);}, []{ return draw_texture(KillproofIcons::Qadim2); }, "1.7", [] {return to_string_long(Killproof::qadim2);}, true},

	// W8
	{static_cast<ImU32>(Killproof::greer), []{ return to_string_short(Killproof::greer); }, []{ return draw_texture(KillproofIcons::Greer); }, "1.8", [] {return to_string_long(Killproof::greer);}, false},
	{static_cast<ImU32>(Killproof::decima), []{ return to_string_short(Killproof::decima); }, []{ return draw_texture(KillproofIcons::Decima); }, "1.8", [] {return to_string_long(Killproof::decima);}, false},
	{static_cast<ImU32>(Killproof::ura), []{ return to_string_short(Killproof::ura); }, []{ return draw_texture(KillproofIcons::Ura); }, "1.8", true},

	// Strikes
	{27, [] {return to_string_short(Killproof::boneskinnerVial);}, []{ return draw_texture(KillproofIcons::Boneskinner_Vial); }, "3", [] {return to_string_long(Killproof::boneskinnerVial);}, true},
	
	// EOD strikes
	{35, [] {return to_string_short(Killproof::maiTrin);}, []{ return draw_texture(KillproofIcons::Mai_Trin); }, "3", [] {return to_string_long(Killproof::maiTrin);}, false},
	{33, [] {return to_string_short(Killproof::ankka);}, []{ return draw_texture(KillproofIcons::Ankka); }, "3", [] {return to_string_long(Killproof::ankka);}, false},
	{37, [] {return to_string_short(Killproof::ministerLi);}, []{ return draw_texture(KillproofIcons::Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLi);}, false},
	{34, [] {return to_string_short(Killproof::harvest);}, []{ return draw_texture(KillproofIcons::Harvest); }, "3", [] {return to_string_long(Killproof::harvest);}, false},
	{36, [] {return to_string_short(Killproof::maiTrinCM);}, []{ return draw_texture(KillproofIcons::Mai_Trin);  }, "3", [] {return to_string_long(Killproof::maiTrinCM);}, false},
	{38, [] {return to_string_short(Killproof::ankkaCM);}, []{ return draw_texture(KillproofIcons::Ankka); }, "3", [] {return to_string_long(Killproof::ankkaCM);}, false},
	{39, [] {return to_string_short(Killproof::ministerLiCM);}, []{ return draw_texture(KillproofIcons::Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLiCM);}, false},
	{40, [] {return to_string_short(Killproof::harvestCM);}, []{ return draw_texture(KillproofIcons::Harvest); }, "3", [] {return to_string_long(Killproof::harvestCM);}, false},
	{42, [] {return to_string_short(Killproof::olc);}, []{ return draw_texture(KillproofIcons::OLC); }, "3", [] {return to_string_long(Killproof::olc);}, false},
	{43, [] {return to_string_short(Killproof::olcCM);}, []{ return draw_texture(KillproofIcons::OLC); }, "3", [] {return to_string_long(Killproof::olcCM);}, false},
	{44, [] {return to_string_short(Killproof::co);}, []{ return draw_texture(KillproofIcons::Dagda); }, "3", [] {return to_string_long(Killproof::co);}, false},
	{45, [] {return to_string_short(Killproof::coCM);}, []{ return draw_texture(KillproofIcons::Dagda); }, "3", [] {return to_string_long(Killproof::coCM);}, false},
	{46, [] {return to_string_short(Killproof::febe);}, []{ return draw_texture(KillproofIcons::Cerus); }, "3", [] {return to_string_long(Killproof::febe);}, false},
	{47, [] {return to_string_short(Killproof::febeCM);}, []{ return draw_texture(KillproofIcons::Cerus); }, "3", [] {return to_string_long(Killproof::febeCM);}, false},

	{41, [] {return to_string_short(Killproof::bananas);}, []{ return draw_texture(KillproofIcons::Bananas); }, "4", [] {return to_string_long(Killproof::bananas);}, false},
};

// Key is the mapId found in the mumbleLink
// Value is a vector of columns that should be shown for that map. The Values are the UserIds from the ColumnSetup.
// TODO: update this when the above vector changes!
static const std::unordered_map<uint32_t, std::vector<size_t>> mapIdToColumnSetup = {
	{1155, {2, 7, 9, 12, 16, 20, 23, 26, 41}}, // Aerodrome
	{1062, {2, 5, 6, 7}}, // W1
	{1149, {2, 8, 9}}, // W2
	{1156, {2, 10, 11, 12}}, // W3
	{1188, {2, 13, 14, 15, 16}}, // W4
	{1264, {2, 17, 18, 19, 20}}, // W5
	{1303, {2, 21, 22, 23}}, // W6
	{1323, {2, 24, 25, 26}}, // W7
	{1564, {std::to_underlying(Killproof::greer), std::to_underlying(Killproof::decima), std::to_underlying(Killproof::ura)}},
	{1370, {2, 27}}, // Eye of the north
	{1432, {2, 35, 36}}, // MaiTrin strike
	{1450, {2, 33, 38}}, // Ankka strike
	{1451, {2, 37, 39}}, // MinisterLi strike
	{1437, {2, 34, 40}}, // HarvestTemple strike
	{1485, {2, 42, 43}}, // OLC Strike
	{1428, {2, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43}}, // Arborstone
	{1509, {2, 44, 45, 46, 47}}, // Wizard's Tower
	{1515, {2, 44, 45}}, // Cosmic Observatory
	{1520, {2, 46, 47}}, // Temple of Febe
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
	bool& getShowHeaderAsText() override;

private:
	template<bool Linked = false>
	bool drawRow(TableColumnIdx pFirstColumnIndex, const Player& pPlayer, bool pHasLinked, bool pTotal = false, bool pTotalText = false);

	template<bool OpenBrowser = false, bool AlignmentActive = false>
	void drawTextColumn(bool& pOpen, const std::string& pText, const std::string& pUsername, const std::atomic<LoadingStatus>& pStatus, bool pTreeNode, bool pIsCommander);

	void openInBrowser(const std::string& username);
};
