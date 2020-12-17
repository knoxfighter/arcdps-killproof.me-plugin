#pragma once

#include <cstdint>
#include <map>
#include <string>

#define amountVal int32_t

enum class Killproof {
	// raid
	li,
	ld,
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
};

const char* toString(Killproof e);

class Killproofs {
	std::map<Killproof, amountVal> killproofs = {
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
	};

public:
	amountVal getAmountFromId(const std::string& id) const;
	amountVal getAmountFromEnum(const Killproof& id) const;

	void setAmountFromId(const std::string& id, const amountVal& amount);
	void setAmountFromId(const int& id, const amountVal& amount);
	void setAmountFromEnum(const Killproof& killproof, const amountVal& amount);
	void setAllTokensFieldsToBlocked();
	void setAllKillproofFieldsToBlocked();
};
