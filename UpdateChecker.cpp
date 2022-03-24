#include "UpdateChecker.h"

#include <string>
#include <thread>

#include "Lang.h"
#include "global.h"
#include "imgui/imgui.h"

void UpdateChecker::Draw() {
	const auto& updateState = GlobalObjects::UPDATE_STATE;
	if (!updateState) {
		// wrongly initialized UpdateChecker, nothing to do here!
		return;
	}
	std::lock_guard guard(updateState->Lock);

	const Status& updateStatus = updateState->UpdateStatus;
	if (updateStatus != Status::Unknown && updateStatus != Status::Dismissed) {
		std::string headerName = lang.translate(LangKey::UpdateWindowHeader);
		headerName.append("##Killproof.me Update");

		bool open = true;
		if (ImGui::Begin(headerName.c_str(), &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
			const Version& currentVersion = *updateState->CurrentVersion;
			const Version& newVersion = updateState->NewVersion;

			ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), lang.translate(LangKey::UpdateDesc).c_str());
			ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "%s: %i.%i.%i",
			                   lang.translate(LangKey::UpdateCurrentVersion).c_str(), currentVersion[0], currentVersion[1],
			                   currentVersion[2]);
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "%s: %i.%i.%i",
			                   lang.translate(LangKey::UpdateNewVersion).c_str(), newVersion[0], newVersion[1],
			                   newVersion[2]);
			if (ImGui::Button(lang.translate(LangKey::UpdateOpenPage).c_str())) {
				std::thread([]() {
					ShellExecuteA(nullptr, nullptr,
					              "https://github.com/knoxfighter/arcdps-killproof.me-plugin/releases/latest", nullptr,
					              nullptr, SW_SHOW);
				}).detach();
			}

			switch (updateStatus) {
				case Status::UpdateAvailable: {
					if (ImGui::Button(lang.translate(LangKey::UpdateAutoButton).c_str())) {
						PerformInstallOrUpdate(*updateState);
					}
					break;
				}
				case Status::UpdateInProgress: {
					ImGui::TextUnformatted(lang.translate(LangKey::UpdateInProgress).c_str());
					break;
				}
				case Status::UpdateSuccessful: {
					ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f),
					                   lang.translate(LangKey::UpdateRestartPending).c_str());
					break;
				}
				case Status::UpdateError: {
					ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), lang.translate(LangKey::UpdateError).c_str());
				}
			}

			ImGui::End();
		}

		if (!open) {
			updateState->UpdateStatus = Status::Dismissed;
		}
	}
}
