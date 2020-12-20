#include "Killproofs.h"

uint8_t convertToPos(const Killproof& kp) {
	switch (kp) {
	case Killproof::li: return 1;
	case Killproof::ld: return 2;
	case Killproof::liLd: return 3;
	case Killproof::uce: return 5;
	case Killproof::ufe: return 6;
	case Killproof::vg:  return 7;
	case Killproof::gorse: return 8;
	case Killproof::sabetha: return 9;
	case Killproof::sloth: return 10;
	case Killproof::matthias: return 11;
	case Killproof::escort: return 12;
	case Killproof::kc: return 13;
	case Killproof::xera: return 14;
	case Killproof::cairn: return 15;
	case Killproof::mo: return 16;
	case Killproof::samarog: return 17;
	case Killproof::deimos: return 18;
	case Killproof::desmina: return 19;
	case Killproof::river: return 20;
	case Killproof::statues: return 21;
	case Killproof::dhuum: return 22;
	case Killproof::ca: return 23;
	case Killproof::twins: return 24;
	case Killproof::qadim: return 25;
	case Killproof::sabir: return 26;
	case Killproof::adina: return 27;
	case Killproof::qadim2: return 28;
	}
}

const char* toString(Killproof e) {
	switch (e) {
	case Killproof::li: return "LI";
	case Killproof::ld: return "LD";
	case Killproof::liLd: return "LI/LD";
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

amountVal Killproofs::getAmountFromId(const std::string& id) const {
	std::lock_guard<std::mutex> guard(mapMutex);

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
	std::lock_guard<std::mutex> guard(mapMutex);
	return killproofs.at(id);
}

void Killproofs::setAmountFromId(const std::string& id, const amountVal& amount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	if (id == "77302") {
		killproofs[Killproof::li] = amount;
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::ld] + amount;
	} else if (id == "88485") {
		killproofs[Killproof::ld] = amount;
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::li] + amount;
	} else if (id == "81743") {
		killproofs[Killproof::uce] = amount;
	} else if (id == "94020") {
		killproofs[Killproof::ufe] = amount;
	} else if (id == "77705") {
		killproofs[Killproof::vg] = amount;
	} else if (id == "77751") {
		killproofs[Killproof::gorse] = amount;
	} else if (id == "77728") {
		killproofs[Killproof::sabetha] = amount;
	} else if (id == "77706") {
		killproofs[Killproof::sloth] = amount;
	} else if (id == "77679") {
		killproofs[Killproof::matthias] = amount;
	} else if (id == "78873") {
		killproofs[Killproof::escort] = amount;
	} else if (id == "78902") {
		killproofs[Killproof::kc] = amount;
	} else if (id == "78942") {
		killproofs[Killproof::xera] = amount;
	} else if (id == "80623") {
		killproofs[Killproof::cairn] = amount;
	} else if (id == "80269") {
		killproofs[Killproof::mo] = amount;
	} else if (id == "80087") {
		killproofs[Killproof::samarog] = amount;
	} else if (id == "80542") {
		killproofs[Killproof::deimos] = amount;
	} else if (id == "85993") {
		killproofs[Killproof::desmina] = amount;
	} else if (id == "85785") {
		killproofs[Killproof::river] = amount;
	} else if (id == "85800") {
		killproofs[Killproof::statues] = amount;
	} else if (id == "85633") {
		killproofs[Killproof::dhuum] = amount;
	} else if (id == "88543") {
		killproofs[Killproof::ca] = amount;
	} else if (id == "88860") {
		killproofs[Killproof::twins] = amount;
	} else if (id == "88645") {
		killproofs[Killproof::qadim] = amount;
	} else if (id == "91270") {
		killproofs[Killproof::sabir] = amount;
	} else if (id == "91246") {
		killproofs[Killproof::adina] = amount;
	} else if (id == "91175") {
		killproofs[Killproof::qadim2] = amount;
	}
}

void Killproofs::setAmountFromId(const int& id, const amountVal& amount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	switch (id) {
	case 77302: 
		killproofs[Killproof::li] = amount;
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::ld] + amount;
		break;
	case 88485: 
		killproofs[Killproof::ld] = amount;
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::li] + amount;
		break;
	case 81743: killproofs[Killproof::uce] = amount;
		break;
	case 94020: killproofs[Killproof::ufe] = amount;
		break;
	case 77705: killproofs[Killproof::vg] = amount;
		break;
	case 77751: killproofs[Killproof::gorse] = amount;
		break;
	case 77728: killproofs[Killproof::sabetha] = amount;
		break;
	case 77706: killproofs[Killproof::sloth] = amount;
		break;
	case 77679: killproofs[Killproof::matthias] = amount;
		break;
	case 78873: killproofs[Killproof::escort] = amount;
		break;
	case 78902: killproofs[Killproof::kc] = amount;
		break;
	case 78942: killproofs[Killproof::xera] = amount;
		break;
	case 80623: killproofs[Killproof::cairn] = amount;
		break;
	case 80269: killproofs[Killproof::mo] = amount;
		break;
	case 80087: killproofs[Killproof::samarog] = amount;
		break;
	case 80542: killproofs[Killproof::deimos] = amount;
		break;
	case 85993: killproofs[Killproof::desmina] = amount;
		break;
	case 85785: killproofs[Killproof::river] = amount;
		break;
	case 85800: killproofs[Killproof::statues] = amount;
		break;
	case 85633: killproofs[Killproof::dhuum] = amount;
		break;
	case 88543: killproofs[Killproof::ca] = amount;
		break;
	case 88860: killproofs[Killproof::twins] = amount;
		break;
	case 88645: killproofs[Killproof::qadim] = amount;
		break;
	case 91270: killproofs[Killproof::sabir] = amount;
		break;
	case 91246: killproofs[Killproof::adina] = amount;
		break;
	case 91175: killproofs[Killproof::qadim2] = amount;
		break;
	default: break;
	}
}

void Killproofs::setAmountFromEnum(const Killproof& killproof, const amountVal& amount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	killproofs[killproof] = amount;

	if (killproof == Killproof::li) {
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::ld] + amount;
	} else if (killproof == Killproof::ld) {
		// set li/ld amount
		killproofs[Killproof::liLd] = killproofs[Killproof::li] + amount;
	}
}

void Killproofs::setAllTokensFieldsToBlocked() {
	std::lock_guard<std::mutex> guard(mapMutex);

	killproofs[Killproof::vg] = -1;
	killproofs[Killproof::gorse] = -1;
	killproofs[Killproof::sabetha] = -1;
	killproofs[Killproof::sloth] = -1;
	killproofs[Killproof::matthias] = -1;
	killproofs[Killproof::escort] = -1;
	killproofs[Killproof::kc] = -1;
	killproofs[Killproof::xera] = -1;
	killproofs[Killproof::cairn] = -1;
	killproofs[Killproof::mo] = -1;
	killproofs[Killproof::samarog] = -1;
	killproofs[Killproof::deimos] = -1;
	killproofs[Killproof::desmina] = -1;
	killproofs[Killproof::river] = -1;
	killproofs[Killproof::statues] = -1;
	killproofs[Killproof::dhuum] = -1;
	killproofs[Killproof::ca] = -1;
	killproofs[Killproof::twins] = -1;
	killproofs[Killproof::qadim] = -1;
	killproofs[Killproof::sabir] = -1;
	killproofs[Killproof::adina] = -1;
	killproofs[Killproof::qadim2] = -1;
}

void Killproofs::setAllKillproofFieldsToBlocked() {
	std::lock_guard<std::mutex> guard(mapMutex);

	killproofs[Killproof::li] = -1;
	killproofs[Killproof::ld] = -1;
	killproofs[Killproof::liLd] = -1;
	killproofs[Killproof::uce] = -1;
	killproofs[Killproof::ufe] = -1;
}

void Killproofs::setBlockedFromId(const int& id) {
	std::lock_guard<std::mutex> guard(mapMutex);

	switch (id) {
	case 77302: 
		killproofs[Killproof::li] = -1;
		// also set li/ld to -1
		killproofs[Killproof::liLd] = -1;
		break;
	case 88485: 
		killproofs[Killproof::ld] = -1;
		// also set li/ld to -1
		killproofs[Killproof::liLd] = -1;
		break;
	case 81743: killproofs[Killproof::uce] = -1;
		break;
	case 94020: killproofs[Killproof::ufe] = -1;
		break;
	case 77705: killproofs[Killproof::vg] = -1;
		break;
	case 77751: killproofs[Killproof::gorse] = -1;
		break;
	case 77728: killproofs[Killproof::sabetha] = -1;
		break;
	case 77706: killproofs[Killproof::sloth] = -1;
		break;
	case 77679: killproofs[Killproof::matthias] = -1;
		break;
	case 78873: killproofs[Killproof::escort] = -1;
		break;
	case 78902: killproofs[Killproof::kc] = -1;
		break;
	case 78942: killproofs[Killproof::xera] = -1;
		break;
	case 80623: killproofs[Killproof::cairn] = -1;
		break;
	case 80269: killproofs[Killproof::mo] = -1;
		break;
	case 80087: killproofs[Killproof::samarog] = -1;
		break;
	case 80542: killproofs[Killproof::deimos] = -1;
		break;
	case 85993: killproofs[Killproof::desmina] = -1;
		break;
	case 85785: killproofs[Killproof::river] = -1;
		break;
	case 85800: killproofs[Killproof::statues] = -1;
		break;
	case 85633: killproofs[Killproof::dhuum] = -1;
		break;
	case 88543: killproofs[Killproof::ca] = -1;
		break;
	case 88860: killproofs[Killproof::twins] = -1;
		break;
	case 88645: killproofs[Killproof::qadim] = -1;
		break;
	case 91270: killproofs[Killproof::sabir] = -1;
		break;
	case 91246: killproofs[Killproof::adina] = -1;
		break;
	case 91175: killproofs[Killproof::qadim2] = -1;
		break;
	default: break;
	}
}
