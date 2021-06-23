#include "Coffers.h"

#include "Settings.h"


void Coffers::addLi(int32_t amount) {
	coffers[Killproof::li] += amount;
	coffers[Killproof::liLd] += amount;
}

void Coffers::addLd(int32_t amount) {
	coffers[Killproof::ld] += amount;
	coffers[Killproof::liLd] += amount;
}

int32_t Coffers::getAmount(const Killproof& id) const {
	std::lock_guard<std::mutex> guard(mapMutex);
	const auto coffersIt = coffers.find(id);
	if (coffersIt == coffers.end()) {
		return 0;
	} else {
		return coffersIt->second;
	}
}

void Coffers::setAmount(const std::string& id, const int32_t& amount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	if (id == "91203") {
		coffers[Killproof::vg] = amount;
		addLi(amount);
	} else if (id == "91215") {
		coffers[Killproof::gorse] = amount;
		addLi(amount);
	} else if (id == "91147") {
		coffers[Killproof::sabetha] = amount;
		addLi(amount);
	} else if (id == "91160") {
		coffers[Killproof::sloth] = amount;
		addLi(amount);
	} else if (id == "91252") {
		coffers[Killproof::matthias] = amount;
		addLi(amount);
	} else if (id == "91262") {
		coffers[Killproof::escort] = amount;
		addLi(amount);
	} else if (id == "91187") {
		coffers[Killproof::kc] = amount;
		addLi(amount);
	} else if (id == "91182") {
		coffers[Killproof::xera] = amount;
		addLi(amount);
	} else if (id == "91186") {
		coffers[Killproof::cairn] = amount;
		addLi(amount);
	} else if (id == "91191") {
		coffers[Killproof::mo] = amount;
		addLi(amount);
	} else if (id == "91267") {
		coffers[Killproof::samarog] = amount;
		addLi(amount);
	} else if (id == "91233") {
		coffers[Killproof::deimos] = amount;
		addLi(amount);
	} else if (id == "91211") {
		coffers[Killproof::desmina] = amount;
		addLd(amount);
	} else if (id == "91244") {
		coffers[Killproof::river] = amount;
		addLd(amount);
	} else if (id == "91138") {
		coffers[Killproof::statues] = amount;
		addLd(amount);
	} else if (id == "91220") {
		coffers[Killproof::dhuum] = amount;
		addLd(amount);
	} else if (id == "91157") {
		coffers[Killproof::ca] = amount;
		addLd(amount);
	} else if (id == "91166") {
		coffers[Killproof::twins] = amount;
		addLd(amount);
	} else if (id == "91237") {
		coffers[Killproof::qadim] = amount;
		addLd(amount);
	} else if (id == "91200") {
		coffers[Killproof::adina] = amount;
		addLd(amount);
	} else if (id == "91241") {
		coffers[Killproof::sabir] = amount;
		addLd(amount);
	} else if (id == "91260") {
		coffers[Killproof::qadim2] = amount;
		addLd(amount);
	}
}

void Coffers::setAmount(const int& id, const int32_t& amount) {
	std::lock_guard<std::mutex> guard(mapMutex);

	switch (id) {
		case 91203:
			coffers[Killproof::vg] = amount;
			addLi(amount);
			break;
		case 91215:
			coffers[Killproof::gorse] = amount;
			addLi(amount);
			break;
		case 91147:
			coffers[Killproof::sabetha] = amount;
			addLi(amount);
			break;
		case 91160:
			coffers[Killproof::sloth] = amount;
			addLi(amount);
			break;
		case 91252:
			coffers[Killproof::matthias] = amount;
			addLi(amount);
			break;
		case 91262:
			coffers[Killproof::escort] = amount;
			addLi(amount);
			break;
		case 91187:
			coffers[Killproof::kc] = amount;
			addLi(amount);
			break;
		case 91182:
			coffers[Killproof::xera] = amount;
			addLi(amount);
			break;
		case 91186:
			coffers[Killproof::cairn] = amount;
			addLi(amount);
			break;
		case 91191:
			coffers[Killproof::mo] = amount;
			addLi(amount);
			break;
		case 91267:
			coffers[Killproof::samarog] = amount;
			addLi(amount);
			break;
		case 91233:
			coffers[Killproof::deimos] = amount;
			addLi(amount);
			break;
		case 91211:
			coffers[Killproof::desmina] = amount;
			addLd(amount);
			break;
		case 91244:
			coffers[Killproof::river] = amount;
			addLd(amount);
			break;
		case 91138:
			coffers[Killproof::statues] = amount;
			addLd(amount);
			break;
		case 91220:
			coffers[Killproof::dhuum] = amount;
			addLd(amount);
			break;
		case 91157:
			coffers[Killproof::ca] = amount;
			addLd(amount);
			break;
		case 91166:
			coffers[Killproof::twins] = amount;
			addLd(amount);
			break;
		case 91237:
			coffers[Killproof::qadim] = amount;
			addLd(amount);
			break;
		case 91200:
			coffers[Killproof::adina] = amount;
			addLd(amount);
			break;
		case 91241:
			coffers[Killproof::sabir] = amount;
			addLd(amount);
			break;
		case 91260:
			coffers[Killproof::qadim2] = amount;
			addLd(amount);
			break;
	}
}

void Coffers::setAllTokensFieldsToBlocked() {
	std::lock_guard<std::mutex> guard(mapMutex);

	coffers[Killproof::vg] = 0;
	coffers[Killproof::gorse] = 0;
	coffers[Killproof::sabetha] = 0;
	coffers[Killproof::sloth] = 0;
	coffers[Killproof::matthias] = 0;
	coffers[Killproof::escort] = 0;
	coffers[Killproof::kc] = 0;
	coffers[Killproof::xera] = 0;
	coffers[Killproof::cairn] = 0;
	coffers[Killproof::mo] = 0;
	coffers[Killproof::samarog] = 0;
	coffers[Killproof::deimos] = 0;
	coffers[Killproof::desmina] = 0;
	coffers[Killproof::river] = 0;
	coffers[Killproof::statues] = 0;
	coffers[Killproof::dhuum] = 0;
	coffers[Killproof::ca] = 0;
	coffers[Killproof::twins] = 0;
	coffers[Killproof::qadim] = 0;
	coffers[Killproof::sabir] = 0;
	coffers[Killproof::adina] = 0;
	coffers[Killproof::qadim2] = 0;
	coffers[Killproof::boneskinnerVial] = 0;
}

void Coffers::setBlockedFromId(const int& id) {
	switch (id) {
	case 91203:
		coffers[Killproof::vg] = 0;
		break;
	case 91215:
		coffers[Killproof::gorse] = 0;
		break;
	case 91147:
		coffers[Killproof::sabetha] = 0;
		break;
	case 91160:
		coffers[Killproof::sloth] = 0;
		break;
	case 91252:
		coffers[Killproof::matthias] = 0;
		break;
	case 91262:
		coffers[Killproof::escort] = 0;
		break;
	case 91187:
		coffers[Killproof::kc] = 0;
		break;
	case 91182:
		coffers[Killproof::xera] = 0;
		break;
	case 91186:
		coffers[Killproof::cairn] = 0;
		break;
	case 91191:
		coffers[Killproof::mo] = 0;
		break;
	case 91267:
		coffers[Killproof::samarog] = 0;
		break;
	case 91233:
		coffers[Killproof::deimos] = 0;
		break;
	case 91211:
		coffers[Killproof::desmina] = 0;
		break;
	case 91244:
		coffers[Killproof::river] = 0;
		break;
	case 91138:
		coffers[Killproof::statues] = 0;
		break;
	case 91220:
		coffers[Killproof::dhuum] = 0;
		break;
	case 91157:
		coffers[Killproof::ca] = 0;
		break;
	case 91166:
		coffers[Killproof::twins] = 0;
		break;
	case 91237:
		coffers[Killproof::qadim] = 0;
		break;
	case 91200:
		coffers[Killproof::adina] = 0;
		break;
	case 91241:
		coffers[Killproof::sabir] = 0;
		break;
	case 91260:
		coffers[Killproof::qadim2] = 0;
		break;
	}
}
