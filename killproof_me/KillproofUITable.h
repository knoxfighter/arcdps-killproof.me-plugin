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
	{JOIN_TIME_ID, [] {return "#";}, []{return nullptr;}, "0", true},
	{ACCOUNT_NAME_ID, [] {return Localization::STranslate(KMT_AccountName);}, []{return nullptr;}, "0", true},
	{CHARACTER_NAME_ID, [] {return Localization::STranslate(KMT_CharacterName);}, []{return nullptr;}, "0", true},
	{KILLPROOF_ID_ID, [] {return Localization::STranslate(KMT_KillproofId);}, []{return nullptr;}, "0", true},
	{SUBGROUP_ID, [] {return Localization::STranslate(KMT_SubgroupText);}, []{return nullptr;}, "0", false},

	// Raids
	// {0, [] {return to_string_short(Killproof::li);}, []{ return GET_TEXTURE(LI, ID_LI); }, "1", true},
	// {1, [] {return to_string_short(Killproof::ld);}, []{ return GET_TEXTURE(LD, ID_LD); }, "1", true},
	{Killproof::liLd, [] {return to_string_short(Killproof::liLd);}, []{ return draw_texture(KillproofIcons::LI); }, "1", true},

	// fractals
	{Killproof::uce, [] {return to_string_short(Killproof::uce);}, []{ return draw_texture(KillproofIcons::UFE); }, "2", true},
	{Killproof::ufe, [] {return to_string_short(Killproof::ufe);}, []{ return draw_texture(KillproofIcons::UFE); }, "2", true},

	// W1
	{Killproof::vg, [] {return to_string_short(Killproof::vg);}, []{ return draw_texture(KillproofIcons::VG); }, "1.1", [] {return to_string_long(Killproof::vg);}, false},
	{Killproof::gorse, [] {return to_string_short(Killproof::gorse);}, []{ return draw_texture(KillproofIcons::Gorse); }, "1.1", [] {return to_string_long(Killproof::gorse);}, false},
	{Killproof::sabetha, [] {return to_string_short(Killproof::sabetha);}, []{ return draw_texture(KillproofIcons::Sabetha); }, "1.1", [] {return to_string_long(Killproof::sabetha);}, false},

	// W2
	{Killproof::sloth, [] {return to_string_short(Killproof::sloth);}, []{ return draw_texture(KillproofIcons::Sloth); }, "1.2", false},
	{Killproof::matthias, [] {return to_string_short(Killproof::matthias);}, []{ return draw_texture(KillproofIcons::Matt); }, "1.2", [] {return to_string_long(Killproof::matthias);}, false},

	// W3
	{Killproof::escort, [] {return to_string_short(Killproof::escort);}, []{ return draw_texture(KillproofIcons::Escort); }, "1.3", false},
	{Killproof::kc, [] {return to_string_short(Killproof::kc);}, []{ return draw_texture(KillproofIcons::KC); }, "1.3", [] {return to_string_long(Killproof::kc);}, false},
	{Killproof::xera, [] {return to_string_short(Killproof::xera);}, []{ return draw_texture(KillproofIcons::Xera); }, "1.3", false},

	// W4
	{Killproof::cairn, [] {return to_string_short(Killproof::cairn);}, []{ return draw_texture(KillproofIcons::Cairn); }, "1.4", [] {return to_string_long(Killproof::cairn);}, false},
	{Killproof::mo, [] {return to_string_short(Killproof::mo);}, []{ return draw_texture(KillproofIcons::MO); }, "1.4", [] {return to_string_long(Killproof::mo);}, false},
	{Killproof::samarog, [] {return to_string_short(Killproof::samarog);}, []{ return draw_texture(KillproofIcons::Samarog); }, "1.4", false},
	{Killproof::deimos, [] {return to_string_short(Killproof::deimos);}, []{ return draw_texture(KillproofIcons::Deimos); }, "1.4", false},

	// W5
	{Killproof::desmina, [] {return to_string_short(Killproof::desmina);}, []{ return draw_texture(KillproofIcons::Desmina); }, "1.5", [] {return to_string_long(Killproof::desmina);}, false},
	{Killproof::river, [] {return to_string_short(Killproof::river);}, []{ return draw_texture(KillproofIcons::River); }, "1.5", [] {return to_string_long(Killproof::river);}, false},
	{Killproof::statues, [] {return to_string_short(Killproof::statues);}, []{ return draw_texture(KillproofIcons::Statues); }, "1.5", false},
	{Killproof::dhuum, [] {return to_string_short(Killproof::dhuum);}, []{ return draw_texture(KillproofIcons::Dhuum); }, "1.5", true},

	// W6
	{Killproof::ca, [] {return to_string_short(Killproof::ca);}, []{ return draw_texture(KillproofIcons::CA); }, "1.6", [] {return to_string_long(Killproof::ca);}, false},
	{Killproof::twins, [] {return to_string_short(Killproof::twins);}, []{ return draw_texture(KillproofIcons::Twins); }, "1.6", [] {return to_string_long(Killproof::twins);}, false},
	{Killproof::qadim, [] {return to_string_short(Killproof::qadim);}, []{ return draw_texture(KillproofIcons::Qadim1); }, "1.6", true},

	// W7
	{Killproof::sabir, [] {return to_string_short(Killproof::sabir);}, []{ return draw_texture(KillproofIcons::Sabir); }, "1.7", false},
	{Killproof::adina, [] {return to_string_short(Killproof::adina);}, []{ return draw_texture(KillproofIcons::Adina); }, "1.7", false},
	{Killproof::qadim2, [] {return to_string_short(Killproof::qadim2);}, []{ return draw_texture(KillproofIcons::Qadim2); }, "1.7", [] {return to_string_long(Killproof::qadim2);}, true},

	// W8
	{Killproof::greer, []{ return to_string_short(Killproof::greer); }, []{ return draw_texture(KillproofIcons::Greer); }, "1.8", [] {return to_string_long(Killproof::greer);}, false},
	{Killproof::decima, []{ return to_string_short(Killproof::decima); }, []{ return draw_texture(KillproofIcons::Decima); }, "1.8", [] {return to_string_long(Killproof::decima);}, false},
	{Killproof::ura, []{ return to_string_short(Killproof::ura); }, []{ return draw_texture(KillproofIcons::Ura); }, "1.8", true},

	{Killproof::greerCM, []{ return to_string_short(Killproof::greerCM); }, []{ return draw_texture(KillproofIcons::Greer); }, "1.8", [] {return to_string_long(Killproof::greerCM);}, false},
	{Killproof::decimaCM, []{ return to_string_short(Killproof::decimaCM); }, []{ return draw_texture(KillproofIcons::Decima); }, "1.8", [] {return to_string_long(Killproof::decimaCM);}, false},
	{Killproof::uraCM, []{ return to_string_short(Killproof::uraCM); }, []{ return draw_texture(KillproofIcons::Ura); }, "1.8", true},

	// Strikes
	{Killproof::boneskinnerVial, [] {return to_string_short(Killproof::boneskinnerVial);}, []{ return draw_texture(KillproofIcons::Boneskinner_Vial); }, "3", [] {return to_string_long(Killproof::boneskinnerVial);}, true},
	
	// EOD strikes
	{Killproof::maiTrin, [] {return to_string_short(Killproof::maiTrin);}, []{ return draw_texture(KillproofIcons::Mai_Trin); }, "3", [] {return to_string_long(Killproof::maiTrin);}, false},
	{Killproof::ankka, [] {return to_string_short(Killproof::ankka);}, []{ return draw_texture(KillproofIcons::Ankka); }, "3", [] {return to_string_long(Killproof::ankka);}, false},
	{Killproof::ministerLi, [] {return to_string_short(Killproof::ministerLi);}, []{ return draw_texture(KillproofIcons::Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLi);}, false},
	{Killproof::harvest, [] {return to_string_short(Killproof::harvest);}, []{ return draw_texture(KillproofIcons::Harvest); }, "3", [] {return to_string_long(Killproof::harvest);}, false},
	{Killproof::maiTrinCM, [] {return to_string_short(Killproof::maiTrinCM);}, []{ return draw_texture(KillproofIcons::Mai_Trin);  }, "3", [] {return to_string_long(Killproof::maiTrinCM);}, false},
	{Killproof::ankkaCM, [] {return to_string_short(Killproof::ankkaCM);}, []{ return draw_texture(KillproofIcons::Ankka); }, "3", [] {return to_string_long(Killproof::ankkaCM);}, false},
	{Killproof::ministerLiCM, [] {return to_string_short(Killproof::ministerLiCM);}, []{ return draw_texture(KillproofIcons::Minister_Li); }, "3", [] {return to_string_long(Killproof::ministerLiCM);}, false},
	{Killproof::harvestCM, [] {return to_string_short(Killproof::harvestCM);}, []{ return draw_texture(KillproofIcons::Harvest); }, "3", [] {return to_string_long(Killproof::harvestCM);}, false},
	{Killproof::olc, [] {return to_string_short(Killproof::olc);}, []{ return draw_texture(KillproofIcons::OLC); }, "3", [] {return to_string_long(Killproof::olc);}, false},
	{Killproof::olcCM, [] {return to_string_short(Killproof::olcCM);}, []{ return draw_texture(KillproofIcons::OLC); }, "3", [] {return to_string_long(Killproof::olcCM);}, false},
	{Killproof::co, [] {return to_string_short(Killproof::co);}, []{ return draw_texture(KillproofIcons::Dagda); }, "3", [] {return to_string_long(Killproof::co);}, false},
	{Killproof::coCM, [] {return to_string_short(Killproof::coCM);}, []{ return draw_texture(KillproofIcons::Dagda); }, "3", [] {return to_string_long(Killproof::coCM);}, false},
	{Killproof::febe, [] {return to_string_short(Killproof::febe);}, []{ return draw_texture(KillproofIcons::Cerus); }, "3", [] {return to_string_long(Killproof::febe);}, false},
	{Killproof::febeCM, [] {return to_string_short(Killproof::febeCM);}, []{ return draw_texture(KillproofIcons::Cerus); }, "3", [] {return to_string_long(Killproof::febeCM);}, false},

	{Killproof::bananas, [] {return to_string_short(Killproof::bananas);}, []{ return draw_texture(KillproofIcons::Bananas); }, "4", [] {return to_string_long(Killproof::bananas);}, false},
};

constexpr const std::vector<size_t> Convert(const std::vector<Killproof> pVector)
{
	std::vector<size_t> res;
	for (auto killproof : pVector)
	{
		res.push_back(std::to_underlying(killproof));
	}
	return res;
}

// Key is the mapId found in the mumbleLink
// Value is a vector of columns that should be shown for that map. The Values are the UserIds from the ColumnSetup.
// TODO: update this when the above vector changes!
static const std::unordered_map<uint32_t, std::vector<size_t>> mapIdToColumnSetup = {
	// Aerodrome
	{1155, Convert({
		Killproof::liLd,
		Killproof::sabetha,
		Killproof::matthias,
		Killproof::xera,
		Killproof::deimos,
		Killproof::dhuum,
		Killproof::qadim,
		Killproof::qadim2,
		Killproof::ura,
		Killproof::uraCM,
		Killproof::bananas
	})},
	// W1
	{1062, Convert({
		Killproof::liLd,
		Killproof::vg,
		Killproof::gorse,
		Killproof::sabetha
	})},
	// W2
	{1149, Convert({
		Killproof::liLd,
		Killproof::sloth,
		Killproof::matthias
	})},
	// W3
	{1156, Convert({
		Killproof::liLd,
		Killproof::escort,
		Killproof::kc,
		Killproof::xera
	})},
	// W4
	{1188, Convert({
		Killproof::liLd,
		Killproof::cairn,
		Killproof::mo,
		Killproof::samarog,
		Killproof::deimos
	})},
	// W5
	{1264, Convert({
		Killproof::liLd,
		Killproof::desmina,
		Killproof::river,
		Killproof::statues,
		Killproof::dhuum
	})},
	// W6
	{1303, Convert({
		Killproof::liLd,
		Killproof::ca,
		Killproof::twins,
		Killproof::qadim
	})},
	// W7
	{1323, Convert({
		Killproof::liLd,
		Killproof::sabir,
		Killproof::adina,
		Killproof::qadim2
	})},
	// W8
	{1564, Convert({
		Killproof::liLd,
		Killproof::greer,
		Killproof::decima,
		Killproof::ura,
		Killproof::greerCM,
		Killproof::decimaCM,
		Killproof::uraCM
	})},
	// Eye of the north
	{1370, Convert({
		Killproof::liLd,
		Killproof::boneskinnerVial
	})},
	// MaiTrin strike
	{1432, Convert({
		Killproof::liLd,
		Killproof::maiTrin,
		Killproof::maiTrinCM
	})},
	// Ankka strike
	{1450, Convert({
		Killproof::liLd,
		Killproof::ankka,
		Killproof::ankkaCM
	})},
	// MinisterLi strike
	{1451, Convert({
		Killproof::liLd,
		Killproof::ministerLi,
		Killproof::ministerLiCM
	})},
	// HarvestTemple strike
	{1437, Convert({
		Killproof::liLd,
		Killproof::harvest,
		Killproof::harvestCM
	})},
	// OLC Strike
	{1485, Convert({
		Killproof::liLd,
		Killproof::olc,
		Killproof::olcCM
	})},
	// Arborstone
	{1428, Convert({
		Killproof::liLd,
		Killproof::maiTrin,
		Killproof::ankka,
		Killproof::ministerLi,
		Killproof::harvest,
		Killproof::olc,
		Killproof::maiTrinCM,
		Killproof::ankkaCM,
		Killproof::ministerLiCM,
		Killproof::harvestCM,
		Killproof::olcCM
	})},
	// Wizard's Tower
	{1509, Convert({
		Killproof::liLd,
		Killproof::co,
		Killproof::febe,
		Killproof::coCM,
		Killproof::febeCM
	})},
	// Cosmic Observatory
	{1515, Convert({
		Killproof::liLd,
		Killproof::co,
		Killproof::coCM
	})},
	// Temple of Febe
	{1520, Convert({
		Killproof::liLd,
		Killproof::febe,
		Killproof::febeCM
	})},
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
	void drawTextColumn(bool& pOpen, const char* pText, const std::string& pUsername, const std::atomic<LoadingStatus>& pStatus, bool pTreeNode, bool pIsCommander);

	void openInBrowser(const std::string& username);
};
