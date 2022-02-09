#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <string>

#define amountVal int32_t

enum class Killproof : int {
	// raid
	li,
	ld,
	liLd,
	// added li and ld
	// fractal
	uce,
	ufe,
	// w1
	vg,
	gorse,
	sabetha,
	// w2
	sloth,
	matthias,
	// w3
	escort,
	kc,
	xera,
	// w4
	cairn,
	mo,
	samarog,
	deimos,
	// w5
	desmina,
	river,
	statues,
	dhuum,
	// w6
	ca,
	twins,
	qadim,
	// w7
	sabir,
	adina,
	qadim2,

	// strikes
	boneskinnerVial,

	// always last element
	// ALWAYS UPDATE AFTER CHANGING THE ENUM
	FINAL_ENTRY,
};

bool defaultHidden(const Killproof& kp);

std::string toString(Killproof e);
inline std::string to_string(Killproof e) {
	return toString(e);
}

class Killproofs {
	std::map<Killproof, amountVal> killproofs = {
		{Killproof::li, -1},
		{Killproof::ld, -1},
		{Killproof::uce, -1},
		{Killproof::ufe, -1},
		{Killproof::vg, -1},
		{Killproof::gorse, -1},
		{Killproof::sabetha, -1},
		{Killproof::sloth, -1},
		{Killproof::matthias, -1},
		{Killproof::escort, -1},
		{Killproof::kc, -1},
		{Killproof::xera, -1},
		{Killproof::cairn, -1},
		{Killproof::mo, -1},
		{Killproof::samarog, -1},
		{Killproof::deimos, -1},
		{Killproof::desmina, -1},
		{Killproof::river, -1},
		{Killproof::statues, -1},
		{Killproof::dhuum, -1},
		{Killproof::ca, -1},
		{Killproof::twins, -1},
		{Killproof::qadim, -1},
		{Killproof::sabir, -1},
		{Killproof::adina, -1},
		{Killproof::qadim2, -1},
		{Killproof::liLd, -1},
		{Killproof::boneskinnerVial, -1},
	};
	mutable std::mutex mapMutex;

public:
	/**
	 * GETTER
	 */
	amountVal getAmount(const std::string& id) const;
	amountVal getAmount(const Killproof& id) const;

	/**
	 * SETTER
	 */
	void setAmountFromId(const std::string& id, const amountVal& amount);
	void setAmountFromId(const int& id, const amountVal& amount);
	void setAmountFromEnum(const Killproof& killproof, const amountVal& amount);
	void setAllTokensFieldsToBlocked();
	void setAllKillproofFieldsToBlocked();
	void setBlockedFromId(const int& id);
};
