#include "UpdateChecker.h"

#include <string>
#include <thread>

#include "Lang.h"
#include "global.h"
#include "imgui/imgui.h"

UpdateChecker updateChecker;

void UpdateChecker::Draw() {
	if (update_status != Status::Unknown && shown) {
		std::string headerName = lang.translate(LangKey::UpdateWindowHeader);
		headerName.append("##Killproof.me Update");
		ImGui::Begin(headerName.c_str(), &shown, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), lang.translate(LangKey::UpdateDesc).c_str());
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "%s: %i.%i.%i", lang.translate(LangKey::UpdateCurrentVersion).c_str(), version[0], version[1],
		                   version[3]);
		ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "%s: %i.%i.%i", lang.translate(LangKey::UpdateNewVersion).c_str(), newVersion[0], newVersion[1],
		                   newVersion[3]);
		if (ImGui::Button(lang.translate(LangKey::UpdateOpenPage).c_str())) {
			std::thread([](){
				ShellExecuteA(nullptr, nullptr, "https://github.com/knoxfighter/arcdps-killproof.me-plugin/releases/latest", nullptr, nullptr, SW_SHOW);
			}).detach();
		}

		switch (update_status) {
		case Status::UpdateAvailable:
			{
				if (ImGui::Button(lang.translate(LangKey::UpdateAutoButton).c_str())) {
					UpdateAutomatically(self_dll);
				}
				break;
			}
		case Status::UpdatingInProgress:
			{
				ImGui::TextUnformatted(lang.translate(LangKey::UpdateInProgress).c_str());
				break;
			}
		case Status::RestartPending:
			{
				ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), lang.translate(LangKey::UpdateRestartPending).c_str());
				break;
			}
		case Status::UpdateError:
			{
			ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), lang.translate(LangKey::UpdateError).c_str());
			}
		}

		ImGui::End();
	}
}
