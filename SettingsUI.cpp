#include "SettingsUI.h"

#include "Settings.h"

#define windowWidth 800
#define leftItemWidth  200
#define rightItemWidth 600

void SettingsUI::draw(const char* title, bool* p_open, ImGuiWindowFlags flags) {
	ImGui::SetNextWindowSize(ImVec2(windowWidth, 650), ImGuiSetCond_FirstUseEver);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(150, 50));
	ImGui::Begin(title, p_open, flags);

	ImGui::Text("Everything selected is shown in the killproofs menu");

	Settings& settings = Settings::instance();
	for (auto& active : settings.getActive()) {
		ImGui::Checkbox(toString(active.first), &active.second);
	}

	ImGui::End();
	ImGui::PopStyleVar(1);
}
