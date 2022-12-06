#pragma once

#include "global.h"
#include "Lang.h"
#include "Killproofs.h"
#include "Player.h"
#include "resource.h"

#include "extension/IconLoader.h"
#include "extension/Windows/MainTable.h"

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

#define GET_TEXTURE_CUSTOM(optional, id) \
	std::invoke([] { \
		auto& iconLoader = IconLoader::instance(); \
		if (!optional) \
			optional = iconLoader.LoadTexture(id); \
		return iconLoader.GetTexture(optional.value()); \
	})

static const std::vector<MainTableColumn> COLUMN_SETUP {
	// general stuff
	{JOIN_TIME_ID, [] {return "#"s;}, []{return nullptr;}, "0", true},
	{ACCOUNT_NAME_ID, [] {return Localization::STranslate(KMT_AccountName);}, []{return nullptr;}, "0", true},
	{CHARACTER_NAME_ID, [] {return Localization::STranslate(KMT_CharacterName);}, []{return nullptr;}, "0", true},
	{KILLPROOF_ID_ID, [] {return Localization::STranslate(KMT_KillproofId);}, []{return nullptr;}, "0", true},
	{SUBGROUP_ID, [] {return Localization::STranslate(KMT_SubgroupText);}, []{return nullptr;}, "0", false},

	// Raids
	{0, [] {return to_string_short(Killproof::li);}, []{ return GET_TEXTURE(LI, ID_LI); }, "1", true},
	{1, [] {return to_string_short(Killproof::ld);}, []{ return GET_TEXTURE(LD, ID_LD); }, "1", true},
	{2, [] {return to_string_short(Killproof::liLd);}, []{ return GET_TEXTURE(LILD, ID_LILD); }, "1", true},

	// fractals
	{3, [] {return to_string_short(Killproof::uce);}, []{ return GET_TEXTURE_CUSTOM(UCE_TEXTURE, ID_UFE); }, "2", true},
	{4, [] {return to_string_short(Killproof::ufe);}, []{ return GET_TEXTURE_CUSTOM(UCE_TEXTURE, ID_UFE); }, "2", true},

	// W1
	{5, [] {return to_string_short(Killproof::vg);}, []{ return GET_TEXTURE(VG, ID_VG); }, "1.1", [] {return to_string_long(Killproof::vg);}, false},
	{6, [] {return to_string_short(Killproof::gorse);}, []{ return GET_TEXTURE(Gorse, ID_Gorse); }, "1.1", [] {return to_string_long(Killproof::gorse);}, false},
	{7, [] {return to_string_short(Killproof::sabetha);}, []{ return GET_TEXTURE(Sabetha, ID_Sabetha); }, "1.1", [] {return to_string_long(Killproof::sabetha);}, false},

	// W2
	{8, [] {return to_string_short(Killproof::sloth);}, []{ return GET_TEXTURE(Sloth, ID_Sloth); }, "1.2", false},
	{9, [] {return to_string_short(Killproof::matthias);}, []{ return GET_TEXTURE(Matt, ID_Matt); }, "1.2", [] {return to_string_long(Killproof::matthias);}, false},

	// W3
	{10, [] {return to_string_short(Killproof::escort);}, []{ return GET_TEXTURE(Escort, ID_Escort); }, "1.3", false},
	{11, [] {return to_string_short(Killproof::kc);}, []{ return GET_TEXTURE(KC, ID_KC); }, "1.3", [] {return to_string_long(Killproof::kc);}, false},
	{12, [] {return to_string_short(Killproof::xera);}, []{ return GET_TEXTURE(Xera, ID_Xera); }, "1.3", false},

	// W4
	{13, [] {return to_string_short(Killproof::cairn);}, []{ return GET_TEXTURE(Cairn, ID_Cairn); }, "1.4", [] {return to_string_long(Killproof::cairn);}, false},
	{14, [] {return to_string_short(Killproof::mo);}, []{ return GET_TEXTURE(MO, ID_MO); }, "1.4", [] {return to_string_long(Killproof::mo);}, false},
	{15, [] {return to_string_short(Killproof::samarog);}, []{ return GET_TEXTURE(Samarog, ID_Samarog); }, "1.4", false},
	{16, [] {return to_string_short(Killproof::deimos);}, []{ return GET_TEXTURE(Deimos, ID_Deimos); }, "1.4", false},

	// W5
	{17, [] {return to_string_short(Killproof::desmina);}, []{ return GET_TEXTURE(Desmina, ID_Desmina); }, "1.5", [] {return to_string_long(Killproof::desmina);}, false},
	{18, [] {return to_string_short(Killproof::river);}, []{ return GET_TEXTURE(River, ID_River); }, "1.5", [] {return to_string_long(Killproof::river);}, false},
	{19, [] {return to_string_short(Killproof::statues);}, []{ return GET_TEXTURE(Statues, ID_Statues); }, "1.5", false},
	{20, [] {return to_string_short(Killproof::dhuum);}, []{ return GET_TEXTURE(Dhuum, ID_Dhuum); }, "1.5", true},

	// W6
	{21, [] {return to_string_short(Killproof::ca);}, []{ return GET_TEXTURE(CA, ID_CA); }, "1.6", [] {return to_string_long(Killproof::ca);}, false},
	{22, [] {return to_string_short(Killproof::twins);}, []{ return GET_TEXTURE(Twins, ID_Twins); }, "1.6", [] {return to_string_long(Killproof::twins);}, false},
	{23, [] {return to_string_short(Killproof::qadim);}, []{ return GET_TEXTURE(Qadim1, ID_Qadim1); }, "1.6", true},

	// W7
	{24, [] {return to_string_short(Killproof::sabir);}, []{ return GET_TEXTURE(Sabir, ID_Sabir); }, "1.7", false},
	{25, [] {return to_string_short(Killproof::adina);}, []{ return GET_TEXTURE(Adina, ID_Adina); }, "1.7", false},
	{26, [] {return to_string_short(Killproof::qadim2);}, []{ return GET_TEXTURE(Qadim2, ID_Qadim2); }, "1.7", [] {return to_string_long(Killproof::qadim2);}, true},

	// Strikes
	{27, [] {return to_string_short(Killproof::boneskinnerVial);}, []{ return GET_TEXTURE(Vial, ID_Boneskinner_Vial); }, "3", [] {return to_string_long(Killproof::boneskinnerVial);}, true},
	
	// EOD strikes
	{35, [] {return to_string_short(Killproof::maiTrin);}, []{ return GET_TEXTURE_CUSTOM(MAI_TRIN_TEXTURE, ID_Mai_Trin); }, "3", [] {return to_string_long(Killproof::maiTrin);}, false},
	{33, [] {return to_string_short(Killproof::ankka);}, []{ return GET_TEXTURE_CUSTOM(ANKKA_TEXTURE, ID_Ankka); }, "3", [] {return to_string_long(Killproof::ankka);}, false},
	{37, [] {return to_string_short(Killproof::ministerLi);}, []{ return GET_TEXTURE_CUSTOM(LI_TEXTURE, ID_Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLi);}, false},
	{34, [] {return to_string_short(Killproof::harvest);}, []{ return GET_TEXTURE_CUSTOM(HARVEST_TEXTURE, ID_Harvest); }, "3", [] {return to_string_long(Killproof::harvest);}, false},
	{36, [] {return to_string_short(Killproof::maiTrinCM);}, []{ return GET_TEXTURE_CUSTOM(MAI_TRIN_TEXTURE, ID_Mai_Trin);  }, "3", [] {return to_string_long(Killproof::maiTrinCM);}, false},
	{38, [] {return to_string_short(Killproof::ankkaCM);}, []{ return GET_TEXTURE_CUSTOM(ANKKA_TEXTURE, ID_Ankka); }, "3", [] {return to_string_long(Killproof::ankkaCM);}, false},
	{39, [] {return to_string_short(Killproof::ministerLiCM);}, []{ return GET_TEXTURE_CUSTOM(LI_TEXTURE, ID_Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLiCM);}, false},
	{40, [] {return to_string_short(Killproof::harvestCM);}, []{ return GET_TEXTURE_CUSTOM(HARVEST_TEXTURE, ID_Harvest); }, "3", [] {return to_string_long(Killproof::harvestCM);}, false},
	{42, [] {return to_string_short(Killproof::olc);}, []{ return GET_TEXTURE_CUSTOM(OLC_TEXTURE, ID_OLC); }, "3", [] {return to_string_long(Killproof::olc);}, false},
	{43, [] {return to_string_short(Killproof::olcCM);}, []{ return GET_TEXTURE_CUSTOM(OLC_TEXTURE, ID_OLC); }, "3", [] {return to_string_long(Killproof::olcCM);}, false},

	{41, [] {return to_string_short(Killproof::bananas);}, []{ return GET_TEXTURE(Bananas, ID_Bananas); }, "4", [] {return to_string_long(Killproof::bananas);}, false},
};

// Key is the mapId found in the mumbleLink
// Value is a vector of columns that should be shown for that map. The Values are the UserIds from the ColumnSetup.
// TODO: update this when the above vector changes!
static const std::unordered_map<uint32_t, std::vector<size_t>> mapIdToColumnSetup = {
	{1155, {0, 1, 2, 7, 9, 12, 16, 20, 23, 26, 41}}, // Aerodrome
	{1062, {0, 1, 2, 5, 6, 7}}, // W1
	{1149, {0, 1, 2, 8, 9}}, // W2
	{1156, {0, 1, 2, 10, 11, 12}}, // W3
	{1188, {0, 1, 2, 13, 14, 15, 16}}, // W4
	{1264, {0, 1, 2, 17, 18, 19, 20}}, // W5
	{1303, {0, 1, 2, 21, 22, 23}}, // W6
	{1323, {0, 1, 2, 24, 25, 26}}, // W7
	{1370, {0, 1, 2, 27}}, // Eye of the north
	{1432, {0, 1, 2, 35, 36}}, // MaiTrin strike
	{1450, {0, 1, 2, 33, 38}}, // Ankka strike
	{1451, {0, 1, 2, 37, 39}}, // MinisterLi strike
	{1437, {0, 1, 2, 34, 40}}, // HarvestTemple strike
	{1485, {0, 1, 2, 42, 43}}, // OLC Strike
	{1428, {0, 1, 2, 33, 34, 35, 36, 37, 38, 39, 40, 42, 43}}, // Arborstone
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
