#include "Killproofs.h"

const char* toString(Killproof e) {
	switch (e) {
	case Killproof::li: return "LI";
	case Killproof::ld: return "LD";
	case Killproof::uce: return "UCE";
	case Killproof::ufe: return "UFE";
	case Killproof::vg: return "VG";
	case Killproof::gorse: return "Gorse";
	case Killproof::sabetha: return "Sabetha";
	case Killproof::sloth: return "Sloth";
	case Killproof::matthias: return "Matthias";
	case Killproof::escort: return "Escort";
	case Killproof::kc: return "KC";
	case Killproof::xera: return "Xera";
	case Killproof::cairn: return "Cairn";
	case Killproof::mo: return "MO";
	case Killproof::samarog: return "Samarog";
	case Killproof::deimos: return "Deimos";
	case Killproof::desmina: return "Desmina";
	case Killproof::river: return "River";
	case Killproof::statues: return "Statues";
	case Killproof::dhuum: return "Dhuum";
	case Killproof::ca: return "CA";
	case Killproof::twins: return "Twins";
	case Killproof::qadim: return "Qadim";
	case Killproof::sabir: return "Sabir";
	case Killproof::adina: return "Adina";
	case Killproof::qadim2: return "Qadim2";
	default: return "Unknown";
	}
}

amountVal Killproofs::getAmountFromId(const std::string& id) {
	if (id == "77302") {
		return killproofs.at(Killproof::li);
	}
	if (id == "88485") {
		return killproofs.at(Killproof::ld);
	}
	if (id == "81743") {
		return killproofs.at(Killproof::uce);
	}
	if (id == "94020") {
		return killproofs.at(Killproof::ufe);
	}
	if (id == "77705") {
		return killproofs.at(Killproof::vg);
	}
	if (id == "77751") {
		return killproofs.at(Killproof::gorse);
	}
	if (id == "77728") {
		return killproofs.at(Killproof::sabetha);
	}
	if (id == "77706") {
		return killproofs.at(Killproof::sloth);
	}
	if (id == "77679") {
		return killproofs.at(Killproof::matthias);
	}
	if (id == "78873") {
		return killproofs.at(Killproof::escort);
	}
	if (id == "78902") {
		return killproofs.at(Killproof::kc);
	}
	if (id == "78942") {
		return killproofs.at(Killproof::xera);
	}
	if (id == "80623") {
		return killproofs.at(Killproof::cairn);
	}
	if (id == "80269") {
		return killproofs.at(Killproof::mo);
	}
	if (id == "80087") {
		return killproofs.at(Killproof::samarog);
	}
	if (id == "80542") {
		return killproofs.at(Killproof::deimos);
	}
	if (id == "85993") {
		return killproofs.at(Killproof::desmina);
	}
	if (id == "85785") {
		return killproofs.at(Killproof::river);
	}
	if (id == "85800") {
		return killproofs.at(Killproof::statues);
	}
	if (id == "85633") {
		return killproofs.at(Killproof::dhuum);
	}
	if (id == "88543") {
		return killproofs.at(Killproof::ca);
	}
	if (id == "88860") {
		return killproofs.at(Killproof::twins);
	}
	if (id == "88645") {
		return killproofs.at(Killproof::qadim);
	}
	if (id == "91270") {
		return killproofs.at(Killproof::sabir);
	}
	if (id == "91246") {
		return killproofs.at(Killproof::adina);
	}
	if (id == "91175") {
		return killproofs.at(Killproof::qadim2);
	}
	return 0;
}

amountVal Killproofs::getAmountFromEnum(const Killproof& id) const {
	return killproofs.at(id);
}

void Killproofs::setAmountFromId(const std::string& id, const amountVal& amount) {
	if (id == "77302") {
		killproofs[Killproof::li] = amount;
	}
	else if (id == "88485") {
		killproofs[Killproof::ld] = amount;
	}
	else if (id == "81743") {
		killproofs[Killproof::uce] = amount;
	}
	else if (id == "94020") {
		killproofs[Killproof::ufe] = amount;
	}
	else if (id == "77705") {
		killproofs[Killproof::vg] = amount;
	}
	else if (id == "77751") {
		killproofs[Killproof::gorse] = amount;
	}
	else if (id == "77728") {
		killproofs[Killproof::sabetha] = amount;
	}
	else if (id == "77706") {
		killproofs[Killproof::sloth] = amount;
	}
	else if (id == "77679") {
		killproofs[Killproof::matthias] = amount;
	}
	else if (id == "78873") {
		killproofs[Killproof::escort] = amount;
	}
	else if (id == "78902") {
		killproofs[Killproof::kc] = amount;
	}
	else if (id == "78942") {
		killproofs[Killproof::xera] = amount;
	}
	else if (id == "80623") {
		killproofs[Killproof::cairn] = amount;
	}
	else if (id == "80269") {
		killproofs[Killproof::mo] = amount;
	}
	else if (id == "80087") {
		killproofs[Killproof::samarog] = amount;
	}
	else if (id == "80542") {
		killproofs[Killproof::deimos] = amount;
	}
	else if (id == "85993") {
		killproofs[Killproof::desmina] = amount;
	}
	else if (id == "85785") {
		killproofs[Killproof::river] = amount;
	}
	else if (id == "85800") {
		killproofs[Killproof::statues] = amount;
	}
	else if (id == "85633") {
		killproofs[Killproof::dhuum] = amount;
	}
	else if (id == "88543") {
		killproofs[Killproof::ca] = amount;
	}
	else if (id == "88860") {
		killproofs[Killproof::twins] = amount;
	}
	else if (id == "88645") {
		killproofs[Killproof::qadim] = amount;
	}
	else if (id == "91270") {
		killproofs[Killproof::sabir] = amount;
	}
	else if (id == "91246") {
		killproofs[Killproof::adina] = amount;
	}
	else if (id == "91175") {
		killproofs[Killproof::qadim2] = amount;
	}
}
