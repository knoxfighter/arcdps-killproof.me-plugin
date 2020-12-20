#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <string>

#define amountVal int32_t

enum class Killproof {
	// raid
	li = 0,
	ld = 1,
	liLd = 26, // added li and ld
	// fractal
	uce = 2,
	ufe = 3,
	// w1
	vg = 4,
	gorse = 5,
	sabetha = 6,
	// w2
	sloth = 7,
	matthias = 8,
	// w3
	escort = 9,
	kc = 10,
	xera = 11,
	// w4
	cairn = 12,
	mo = 13,
	samarog = 14,
	deimos = 15,
	// w5
	desmina = 16,
	river = 17,
	statues = 18,
	dhuum = 19,
	// w6
	ca = 20,
	twins = 21,
	qadim = 22,
	// w7
	sabir = 23,
	adina = 24,
	qadim2 = 25,
};
uint8_t convertToPos(const Killproof& kp);

// cannot use this operator, it would be ambiguous, cause of a msvc++ compiler bug
// bool operator<(const Killproof& lhs, const Killproof& rhs);
// use this comparison object as Compare implementation
struct comparatorKillProof {
	bool operator()(const Killproof& lhs, const Killproof& rhs) const {
		return convertToPos(lhs) < convertToPos(rhs);
	}
};


const char* toString(Killproof e);

class Killproofs {
	std::map < Killproof, amountVal, comparatorKillProof> killproofs = {
		{Killproof::li, 0},
		{Killproof::ld, 0},
		{Killproof::uce, 0},
		{Killproof::ufe, 0},
		{Killproof::vg, 0},
		{Killproof::gorse, 0},
		{Killproof::sabetha, 0},
		{Killproof::sloth, 0},
		{Killproof::matthias, 0},
		{Killproof::escort, 0},
		{Killproof::kc, 0},
		{Killproof::xera, 0},
		{Killproof::cairn, 0},
		{Killproof::mo, 0},
		{Killproof::samarog, 0},
		{Killproof::deimos, 0},
		{Killproof::desmina, 0},
		{Killproof::river, 0},
		{Killproof::statues, 0},
		{Killproof::dhuum, 0},
		{Killproof::ca, 0},
		{Killproof::twins, 0},
		{Killproof::qadim, 0},
		{Killproof::sabir, 0},
		{Killproof::adina, 0},
		{Killproof::qadim2, 0},
		{Killproof::liLd, 0},
	};
	mutable std::mutex mapMutex;

public:
	/**
	 * GETTER
	 */
	amountVal getAmountFromId(const std::string& id) const;
	amountVal getAmountFromEnum(const Killproof& id) const;

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
