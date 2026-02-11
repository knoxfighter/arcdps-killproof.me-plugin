#pragma once

#include "resource.h"

#include <ArcdpsExtension/IconLoader.h>
#include <ArcdpsExtension/map.h>
#include <magic_enum/magic_enum_all.hpp>

#define generate_icon_list_enum(val) val
#define generate_icon_list_vector(val) ID_##val

#define generate_icon_list(...) \
	enum class KillproofIcons { \
	MAP_LIST(generate_icon_list_enum, __VA_ARGS__) \
	}; \
	static constexpr std::array ICON_LIST { \
	MAP_LIST(generate_icon_list_vector, __VA_ARGS__) \
	}

generate_icon_list(
	LI ,
	UFE ,
	VG ,
	Gorse ,
	Sabetha ,
	Sloth ,
	Matt ,
	Escort ,
	KC ,
	Xera ,
	Cairn ,
	MO ,
	Samarog ,
	Deimos ,
	Desmina ,
	River ,
	Statues ,
	Dhuum ,
	CA ,
	Twins ,
	Qadim1 ,
	Sabir ,
	Adina ,
	Qadim2 ,
	Greer,
	Decima,
	Ura,
	Boneskinner_Vial ,
	Mai_Trin ,
	Ankka ,
	Minister_Li ,
	Harvest ,
	OLC ,
	Dagda ,
	Cerus ,
	Bananas,
	Commander_White,
	Sandcastle
);

static_assert(magic_enum::enum_count<KillproofIcons>() == ICON_LIST.size());

inline void RegisterIcons() {
	auto& iconLoader = ArcdpsExtension::IconLoader::instance();

	magic_enum::enum_for_each<KillproofIcons>([&] (auto val) {
		constexpr KillproofIcons iconId = val;

		iconLoader.RegisterResource(iconId, ICON_LIST[std::to_underlying(iconId)]);
	});
}
