#pragma once

#include <cstdint>
#include <map>
#include <mutex>
#include <string>

#define amountVal int32_t

/**
 * The ID of each killproof item.
 * This also is the UserID of the `MainTable`, make sure it is corresponding to it.
 */
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

	// EOD strikes
	ankka = 33,
	harvest = 34,
	maiTrin = 35,
	maiTrinCM = 36,
	ministerLi = 37,
	ankkaCM = 38,
	ministerLiCM = 39,

	// no final entry anymore, use `magic_enum` to iterate over the enum.
};

bool defaultHidden(const Killproof& kp);

const std::string& toString(Killproof e);

inline const std::string& to_string(Killproof e) {
	return toString(e);
}

class Killproofs {
	std::map<Killproof, amountVal> killproofs;
	mutable std::mutex mapMutex;

public:
	/**
	 * GETTER
	 */
	std::optional<amountVal> GetAmount(const Killproof& id) const;

	/**
	 * SETTER
	 */
	void SetAmount(Killproof pId, const amountVal& pAmount);

	template <bool CofferIds = false>
	void SetAmount(const std::string& id, const amountVal& amount) {
		SetAmount<CofferIds>(std::stoi(id), amount);
	}

	template <bool CofferIds = false>
	void SetAmount(const int& id, const amountVal& amount) {
		std::lock_guard<std::mutex> guard(mapMutex);

		if constexpr (CofferIds) {
			switch (id) {
				case 91203:
					killproofs[Killproof::vg] = amount;
					break;
				case 91215:
					killproofs[Killproof::gorse] = amount;
					break;
				case 91147:
					killproofs[Killproof::sabetha] = amount;
					break;
				case 91160:
					killproofs[Killproof::sloth] = amount;
					break;
				case 91252:
					killproofs[Killproof::matthias] = amount;
					break;
				case 91262:
					killproofs[Killproof::escort] = amount;
					break;
				case 91187:
					killproofs[Killproof::kc] = amount;
					break;
				case 91182:
					killproofs[Killproof::xera] = amount;
					break;
				case 91186:
					killproofs[Killproof::cairn] = amount;
					break;
				case 91191:
					killproofs[Killproof::mo] = amount;
					break;
				case 91267:
					killproofs[Killproof::samarog] = amount;
					break;
				case 91233:
					killproofs[Killproof::deimos] = amount;
					break;
				case 91211:
					killproofs[Killproof::desmina] = amount;
					break;
				case 91244:
					killproofs[Killproof::river] = amount;
					break;
				case 91138:
					killproofs[Killproof::statues] = amount;
					break;
				case 91220:
					killproofs[Killproof::dhuum] = amount;
					break;
				case 91157:
					killproofs[Killproof::ca] = amount;
					break;
				case 91166:
					killproofs[Killproof::twins] = amount;
					break;
				case 91237:
					killproofs[Killproof::qadim] = amount;
					break;
				case 91200:
					killproofs[Killproof::adina] = amount;
					break;
				case 91241:
					killproofs[Killproof::sabir] = amount;
					break;
				case 91260:
					killproofs[Killproof::qadim2] = amount;
					break;
			}
		} else {
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
				case 81743: 
					killproofs[Killproof::uce] = amount;
					break;
				case 94020: 
					killproofs[Killproof::ufe] = amount;
					break;
				case 77705: 
					killproofs[Killproof::vg] = amount;
					break;
				case 77751: 
					killproofs[Killproof::gorse] = amount;
					break;
				case 77728: 
					killproofs[Killproof::sabetha] = amount;
					break;
				case 77706:
					killproofs[Killproof::sloth] = amount;
					break;
				case 77679: 
					killproofs[Killproof::matthias] = amount;
					break;
				case 78873: 
					killproofs[Killproof::escort] = amount;
					break;
				case 78902: 
					killproofs[Killproof::kc] = amount;
					break;
				case 78942: 
					killproofs[Killproof::xera] = amount;
					break;
				case 80623: 
					killproofs[Killproof::cairn] = amount;
					break;
				case 80269: 
					killproofs[Killproof::mo] = amount;
					break;
				case 80087: 
					killproofs[Killproof::samarog] = amount;
					break;
				case 80542: 
					killproofs[Killproof::deimos] = amount;
					break;
				case 85993: 
					killproofs[Killproof::desmina] = amount;
					break;
				case 85785: 
					killproofs[Killproof::river] = amount;
					break;
				case 85800: 
					killproofs[Killproof::statues] = amount;
					break;
				case 85633: 
					killproofs[Killproof::dhuum] = amount;
					break;
				case 88543: 
					killproofs[Killproof::ca] = amount;
					break;
				case 88860: 
					killproofs[Killproof::twins] = amount;
					break;
				case 88645: 
					killproofs[Killproof::qadim] = amount;
					break;
				case 91270: 
					killproofs[Killproof::sabir] = amount;
					break;
				case 91246: 
					killproofs[Killproof::adina] = amount;
					break;
				case 91175: 
					killproofs[Killproof::qadim2] = amount;
					break;
				case 93781: 
					killproofs[Killproof::boneskinnerVial] = amount;
					break;
				case 95982: 
					killproofs[Killproof::ankka] = amount;
					break;
				case 96638:
					killproofs[Killproof::ankkaCM] = amount;
					break;
				case 97132:
					killproofs[Killproof::harvest] = amount;
					break;
				case 95638:
					killproofs[Killproof::maiTrin] = amount;
					break;
				case 97269:
					killproofs[Killproof::maiTrinCM] = amount;
					break;
				case 97451:
					killproofs[Killproof::ministerLi] = amount;
					break;
				case 96419:
					killproofs[Killproof::ministerLiCM] = amount;
					break;
				default: break;
			}
		}
	}
};
