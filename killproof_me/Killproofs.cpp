#include "Killproofs.h"

#include "Lang.h"

#include "extension/Localization.h"

bool defaultHidden(const Killproof& kp) {
	switch (kp) {
	case Killproof::li:
	case Killproof::ld:
	case Killproof::liLd:
	case Killproof::uce:
	case Killproof::ufe:
	case Killproof::dhuum:
	case Killproof::qadim:
	case Killproof::qadim2:
	case Killproof::boneskinnerVial:
		return false;
	case Killproof::vg:
	case Killproof::gorse:
	case Killproof::sabetha:
	case Killproof::sloth:
	case Killproof::matthias:
	case Killproof::escort:
	case Killproof::kc:
	case Killproof::xera:
	case Killproof::cairn:
	case Killproof::mo:
	case Killproof::samarog:
	case Killproof::deimos:
	case Killproof::desmina:
	case Killproof::river:
	case Killproof::statues:
	case Killproof::ca:
	case Killproof::twins:
	case Killproof::sabir:
	case Killproof::adina:
		return true;
	default: return false;
	}
}

const std::string& toString(Killproof e) {
	switch (e) {
	case Killproof::li: return Localization::STranslate(KMT_LI);
	case Killproof::ld: return Localization::STranslate(KMT_Ld);
	case Killproof::liLd: return Localization::STranslate(KMT_LiLd);
	case Killproof::uce: return Localization::STranslate(KMT_Uce);
	case Killproof::ufe: return Localization::STranslate(KMT_Ufe);
	case Killproof::vg: return Localization::STranslate(KMT_Vg);
	case Killproof::gorse: return Localization::STranslate(KMT_Gorse);
	case Killproof::sabetha: return Localization::STranslate(KMT_Sabetha);
	case Killproof::sloth: return Localization::STranslate(KMT_Sloth);
	case Killproof::matthias: return Localization::STranslate(KMT_Matthias);
	case Killproof::escort: return Localization::STranslate(KMT_Escort);
	case Killproof::kc: return Localization::STranslate(KMT_Kc);
	case Killproof::xera: return Localization::STranslate(KMT_Xera);
	case Killproof::cairn: return Localization::STranslate(KMT_Cairn);
	case Killproof::mo: return Localization::STranslate(KMT_Mo);
	case Killproof::samarog: return Localization::STranslate(KMT_Samarog);
	case Killproof::deimos: return Localization::STranslate(KMT_Deimos);
	case Killproof::desmina: return Localization::STranslate(KMT_Desmina);
	case Killproof::river: return Localization::STranslate(KMT_River);
	case Killproof::statues: return Localization::STranslate(KMT_Statues);
	case Killproof::dhuum: return Localization::STranslate(KMT_Dhuum);
	case Killproof::ca: return Localization::STranslate(KMT_Ca);
	case Killproof::twins: return Localization::STranslate(KMT_Twins);
	case Killproof::qadim: return Localization::STranslate(KMT_Qadim);
	case Killproof::sabir: return Localization::STranslate(KMT_Sabir);
	case Killproof::adina: return Localization::STranslate(KMT_Adina);
	case Killproof::qadim2: return Localization::STranslate(KMT_Qadim2);
	case Killproof::boneskinnerVial: return Localization::STranslate(KMT_BoneskinnerVial);
	case Killproof::ankka: return Localization::STranslate(KMT_Ankka);
	case Killproof::ministerLi: return Localization::STranslate(KMT_MinisterLi);
	case Killproof::harvest: return Localization::STranslate(KMT_Harvest);
	case Killproof::maiTrin: return Localization::STranslate(KMT_MaiTrin);
	case Killproof::maiTrinCM: return Localization::STranslate(KMT_MaiTrinCM);
	case Killproof::ankkaCM: return Localization::STranslate(KMT_AnkkaCM);
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
