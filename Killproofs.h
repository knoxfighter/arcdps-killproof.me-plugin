#pragma once

#include <cstdint>
#include <map>
#include <string>

#define amountVal uint16_t

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
	std::map<Killproof, amountVal> killproofs;

public:
	amountVal getAmountFromId(const std::string& id) const;
	amountVal getAmountFromEnum(const Killproof& id) const;

	void setAmountFromId(const std::string& id, const amountVal& amount);
	void setAmountFromId(const int& id, const uint16_t& amount);
	void setAmountFromEnum(const Killproof& killproof, const amountVal& amount);
};
