#include "arcdps_structs.h"

#include "Lang.h"

std::string to_string(Alignment alignment) {
	switch (alignment) {
	case Alignment::Left: return lang.translate(LangKey::Left);
	case Alignment::Center: return lang.translate(LangKey::Center);
	case Alignment::Right: return lang.translate(LangKey::Right);
	default: return "Unknown";
	}
}
