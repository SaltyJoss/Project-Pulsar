
#include "pch.h"

#include <imgui.h>
#include "Scene/DebugPanel.h"
#include <io.h>

#include "EngineLib/LogMacros.h"

void gui::DebugPanel::render() {
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 310, ImGui::GetIO().DisplaySize.y - 200), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.129f, 0.129f, 0.129f, 0.8f));
    ImGui::Begin("Debug Panel", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginTabBar("Debug Tabs")) {
        if (ImGui::BeginTabItem("Log")) {
            renderLog();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Error List")) {
            renderErrors();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
	ImGui::PopStyleColor();
}

void gui::DebugPanel::renderLog() {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.925f));
    ImGui::BeginChild("LogChild", ImVec2(0, -30), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        
    for (const auto& entry : entries) {
        ImVec4 col = entry.isError ? ImVec4(1, 0.3f, 0.3f, 1) : ImVec4(1, 1, 1, 1);
        ImGui::PushStyleColor(ImGuiCol_Text, col);
        ImGui::TextUnformatted(entry.text.c_str());
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();
	ImGui::PopStyleColor();

    if (ImGui::Button("Clear")) entries.clear();
    ImGui::SameLine();
    if (ImGui::Button("Copy")) ImGui::LogToClipboard();
}

void gui::DebugPanel::renderErrors() {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.925f));
    ImGui::BeginChild("ErrorChild", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
    for (const auto& entry : entries)
        if (entry.isError)
            ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), "%s", entry.text.c_str());
    ImGui::EndChild();
	ImGui::PopStyleColor();
}

void gui::DebugPanel::addLog(const std::string& msg, bool error) { entries.push_back({ msg, error }); }
ImVec4 gui::DebugPanel::getColour(bool error) const { return error ? ImVec4(1, 0, 0, 1) : ImVec4(1, 1, 1, 1); }
