#include "Killproofs.h"

#include "Lang.h"

#include "ArcdpsExtension/Localization.h"

using namespace ArcdpsExtension;

std::string_view toStringShort(Killproof e) {
	switch (e) {
	// case Killproof::li: return Localization::STranslate(KMT_Li_Short);
	// case Killproof::ld: return Localization::STranslate(KMT_Ld_Short);
	case Killproof::liLd: return Localization::STranslate(KMT_LiLd_Short);

	case Killproof::uce: return Localization::STranslate(KMT_Uce_Short);
	case Killproof::ufe: return Localization::STranslate(KMT_Ufe_Short);

	case Killproof::vg: return Localization::STranslate(KMT_Vg_Short);
	case Killproof::gorse: return Localization::STranslate(KMT_Gorse_Short);
	case Killproof::sabetha: return Localization::STranslate(KMT_Sabetha_Short);

	case Killproof::sloth: return Localization::STranslate(KMT_Sloth_Short);
	case Killproof::matthias: return Localization::STranslate(KMT_Matthias_Short);

	case Killproof::escort: return Localization::STranslate(KMT_Escort_Short);
	case Killproof::kc: return Localization::STranslate(KMT_Kc_Short);
	case Killproof::xera: return Localization::STranslate(KMT_Xera_Short);

	case Killproof::cairn: return Localization::STranslate(KMT_Cairn_Short);
	case Killproof::mo: return Localization::STranslate(KMT_Mo_Short);
	case Killproof::samarog: return Localization::STranslate(KMT_Samarog_Short);
	case Killproof::deimos: return Localization::STranslate(KMT_Deimos_Short);

	case Killproof::desmina: return Localization::STranslate(KMT_Desmina_Short);
	case Killproof::river: return Localization::STranslate(KMT_River_Short);
	case Killproof::statues: return Localization::STranslate(KMT_Statues_Short);
	case Killproof::dhuum: return Localization::STranslate(KMT_Dhuum_Short);

	case Killproof::ca: return Localization::STranslate(KMT_Ca_Short);
	case Killproof::twins: return Localization::STranslate(KMT_Twins_Short);
	case Killproof::qadim: return Localization::STranslate(KMT_Qadim_Short);

	case Killproof::sabir: return Localization::STranslate(KMT_Sabir_Short);
	case Killproof::adina: return Localization::STranslate(KMT_Adina_Short);
	case Killproof::qadim2: return Localization::STranslate(KMT_Qadim2_Short);

	case Killproof::greer: return Localization::STranslate(KMT_Greer_Short);
	case Killproof::decima: return Localization::STranslate(KMT_Decima_Short);
	case Killproof::ura: return Localization::STranslate(KMT_Ura_Short);
	case Killproof::greerCM: return Localization::STranslate(KMT_GreerCM_Short);
	case Killproof::decimaCM: return Localization::STranslate(KMT_DecimaCM_Short);
	case Killproof::uraCM: return Localization::STranslate(KMT_UraCM_Short);

	case Killproof::boneskinnerVial: return Localization::STranslate(KMT_BoneskinnerVial_Short);
	case Killproof::ankka: return Localization::STranslate(KMT_Ankka_Short);
	case Killproof::ministerLi: return Localization::STranslate(KMT_MinisterLi_Short);
	case Killproof::harvest: return Localization::STranslate(KMT_Harvest_Short);
	case Killproof::maiTrin: return Localization::STranslate(KMT_MaiTrin_Short);
	case Killproof::maiTrinCM: return Localization::STranslate(KMT_MaiTrinCM_Short);
	case Killproof::ankkaCM: return Localization::STranslate(KMT_AnkkaCM_Short);
	case Killproof::ministerLiCM: return Localization::STranslate(KMT_MinisterLiCM_Short);
	case Killproof::harvestCM: return Localization::STranslate(KMT_HarvestCM_Short);
	case Killproof::olc: return Localization::STranslate(KMT_OLC_Short);
	case Killproof::olcCM: return Localization::STranslate(KMT_OLCCM_Short);
	case Killproof::co: return Localization::STranslate(KMT_CO_Short);
	case Killproof::coCM: return Localization::STranslate(KMT_COCM_Short);
	case Killproof::febe: return Localization::STranslate(KMT_FEBE_Short);
	case Killproof::febeCM: return Localization::STranslate(KMT_FEBECM_Short);
	case Killproof::kela: return Localization::STranslate(KMT_Kela_Short);

	case Killproof::bananas: return Localization::STranslate(KMT_Bananas);
	default: return Localization::STranslate(ET_Unknown);
	}
}

std::string_view toStringLong(Killproof e) {
	switch (e) {
	case Killproof::vg: return Localization::STranslate(KMT_Vg_Long);
	case Killproof::gorse: return Localization::STranslate(KMT_Gorse_Long);
	case Killproof::sabetha: return Localization::STranslate(KMT_Sabetha_Long);

	case Killproof::matthias: return Localization::STranslate(KMT_Matthias_Long);
	case Killproof::kc: return Localization::STranslate(KMT_Kc_Long);

	case Killproof::cairn: return Localization::STranslate(KMT_Cairn_Long);
	case Killproof::mo: return Localization::STranslate(KMT_Mo_Long);

	case Killproof::desmina: return Localization::STranslate(KMT_Desmina_Long);
	case Killproof::river: return Localization::STranslate(KMT_River_Long);

	case Killproof::ca: return Localization::STranslate(KMT_Ca_Long);
	case Killproof::twins: return Localization::STranslate(KMT_Twins_Long);

	case Killproof::qadim2: return Localization::STranslate(KMT_Qadim2_Long);

	case Killproof::greer: return Localization::STranslate(KMT_Greer_Long);
	case Killproof::greerCM: return Localization::STranslate(KMT_GreerCM_Long);
	case Killproof::decima: return Localization::STranslate(KMT_Decima_Long);
	case Killproof::decimaCM: return Localization::STranslate(KMT_DecimaCM_Long);

	case Killproof::boneskinnerVial: return Localization::STranslate(KMT_BoneskinnerVial_Long);
	case Killproof::ankka: return Localization::STranslate(KMT_Ankka_Long);
	case Killproof::ministerLi: return Localization::STranslate(KMT_MinisterLi_Long);
	case Killproof::harvest: return Localization::STranslate(KMT_Harvest_Long);
	case Killproof::maiTrin: return Localization::STranslate(KMT_MaiTrin_Long);
	case Killproof::maiTrinCM: return Localization::STranslate(KMT_MaiTrinCM_Long);
	case Killproof::ankkaCM: return Localization::STranslate(KMT_AnkkaCM_Long);
	case Killproof::ministerLiCM: return Localization::STranslate(KMT_MinisterLiCM_Long);
	case Killproof::harvestCM: return Localization::STranslate(KMT_HarvestCM_Long);
	case Killproof::olc: return Localization::STranslate(KMT_OLC_Long);
	case Killproof::olcCM: return Localization::STranslate(KMT_OLCCM_Long);
	case Killproof::co: return Localization::STranslate(KMT_CO_Long);
	case Killproof::coCM: return Localization::STranslate(KMT_COCM_Long);
	case Killproof::febe: return Localization::STranslate(KMT_FEBE_Long);
	case Killproof::febeCM: return Localization::STranslate(KMT_FEBECM_Long);
	case Killproof::kela: return Localization::STranslate(KMT_Kela_Long);

	case Killproof::bananas: return Localization::STranslate(KMT_Bananas);
	default: return Localization::STranslate(ET_Unknown);
	}
}

std::optional<amountVal> Killproofs::GetAmount(const Killproof& id) const {
	std::lock_guard<std::mutex> guard(mapMutex);
	const auto killproofIt = killproofs.find(id);
	if (killproofIt == killproofs.end()) {
		return std::nullopt;
	}
	return killproofIt->second;
}

void Killproofs::SetAmount(Killproof pId, const int32_t& pAmount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	killproofs[pId] = pAmount;
}
