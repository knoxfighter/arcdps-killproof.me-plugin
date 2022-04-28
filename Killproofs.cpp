#include "Killproofs.h"

#include "Lang.h"

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

std::string toString(Killproof e) {
	switch (e) {
	case Killproof::li: return lang.translate(LangKey::LI);
	case Killproof::ld: return lang.translate(LangKey::Ld);
	case Killproof::liLd: return lang.translate(LangKey::LiLd);
	case Killproof::uce: return lang.translate(LangKey::Uce);
	case Killproof::ufe: return lang.translate(LangKey::Ufe);
	case Killproof::vg: return lang.translate(LangKey::Vg);
	case Killproof::gorse: return lang.translate(LangKey::Gorse);
	case Killproof::sabetha: return lang.translate(LangKey::Sabetha);
	case Killproof::sloth: return lang.translate(LangKey::Sloth);
	case Killproof::matthias: return lang.translate(LangKey::Matthias);
	case Killproof::escort: return lang.translate(LangKey::Escort);
	case Killproof::kc: return lang.translate(LangKey::Kc);
	case Killproof::xera: return lang.translate(LangKey::Xera);
	case Killproof::cairn: return lang.translate(LangKey::Cairn);
	case Killproof::mo: return lang.translate(LangKey::Mo);
	case Killproof::samarog: return lang.translate(LangKey::Samarog);
	case Killproof::deimos: return lang.translate(LangKey::Deimos);
	case Killproof::desmina: return lang.translate(LangKey::Desmina);
	case Killproof::river: return lang.translate(LangKey::River);
	case Killproof::statues: return lang.translate(LangKey::Statues);
	case Killproof::dhuum: return lang.translate(LangKey::Dhuum);
	case Killproof::ca: return lang.translate(LangKey::Ca);
	case Killproof::twins: return lang.translate(LangKey::Twins);
	case Killproof::qadim: return lang.translate(LangKey::Qadim);
	case Killproof::sabir: return lang.translate(LangKey::Sabir);
	case Killproof::adina: return lang.translate(LangKey::Adina);
	case Killproof::qadim2: return lang.translate(LangKey::Qadim2);
	case Killproof::boneskinnerVial: return lang.translate(LangKey::BoneskinnerVial);
	default: return lang.translate(LangKey::DefaultKp);
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
