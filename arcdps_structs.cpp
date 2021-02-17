#include "arcdps_structs.h"

std::string to_string(Alignment alignment) {
	switch (alignment) {
	case Alignment::Left: return "Left";
	case Alignment::Center: return "Center";
	case Alignment::Right: return "Right";
	default: return "Unknown";
	}
}
