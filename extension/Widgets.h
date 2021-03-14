#pragma once

#include "arcdps_structs.h"
#include "../imgui/imgui.h"

static inline ImVec2 operator+(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x + rhs, lhs.y + rhs); }

namespace ImGuiEx {
	bool Spinner(const char* label, float radius, float thickness, const ImU32& color);
	bool SpinnerAligned(const char* label, float radius, float thickness, const ImU32& color, Alignment alignment);
	void AlignedTextColumn(Alignment alignment, const char* text, ...);
	void TableHeader(const char* label, bool show_label, ImTextureID texture, Alignment alignment = Alignment::Left);
}
