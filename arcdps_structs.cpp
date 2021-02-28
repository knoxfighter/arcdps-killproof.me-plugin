#include "arcdps_structs.h"

#include "Lang.h"

std::string to_string(Alignment alignment) {
	switch (alignment) {
	case Alignment::Left: return Lang::translate(LangKey::Left);
	case Alignment::Center: return Lang::translate(LangKey::Center);
	case Alignment::Right: return Lang::translate(LangKey::Right);
	default: return "Unknown";
	}
}
