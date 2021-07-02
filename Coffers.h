#pragma once

#include "Killproofs.h"

class Coffers {
	std::map<Killproof, amountVal> coffers = {
			{Killproof::li, 0},
			{Killproof::ld, 0},
			{Killproof::liLd, 0},
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
	mutable std::mutex mapMutex;

public:
	/**
	 * GETTER
	 */
	amountVal getAmount(const Killproof& id) const;

	/**
	 * SETTER
	 */
	void setAmount(const std::string& id, const amountVal& amount);
	void setAmount(const int& id, const amountVal& amount);
	void setAllTokensFieldsToBlocked();
	void setBlockedFromId(const int& id);
};

