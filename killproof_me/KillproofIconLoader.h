#pragma once

#include "extension/IconLoader.h"

enum class IconId {
	LI,
	LD,
	LiLd,
	Uce,
	Ufe,
	VG,
	Gorse,
	Sabetha,
	Sloth,
	Matthias,
	Escort,
	KC,
	Xera,
	Cairn,
	MO,
	Samarog,
	Deimos,
	// w5
	Desmina,
	River,
	Statues,
	Dhuum,
	// w6
	CA,
	Twins,
	Qadim,
	Sabir,
	Adina,
	Qadim2,
	BoneskinnerVial,
	Ankka,
	Harvest,
	MaiTrin,
	MinisterLi,
	Commander_White,
};

using KillproofIconLoader = IconLoader<IconId>;
