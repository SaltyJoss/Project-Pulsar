#include "pch.h"
#include "Styles.h"

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace gui {
    void Styles::DarkMode() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // --- Rounding ---
        style.WindowRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;

        // --- Padding & spacing ---
        style.WindowPadding = ImVec2(6, 6);
        style.FramePadding = ImVec2(6, 4);
        style.ItemSpacing = ImVec2(6, 4);
        style.ItemInnerSpacing = ImVec2(4, 4);

        // --- Borders & separators ---
        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.TabBorderSize = 1.0f;
        style.SeparatorTextBorderSize = 1.0f;

        // --- Colors ---
        colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
        colors[ImGuiCol_Border] = ImVec4(0.29f, 0.29f, 0.29f, 1.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
        colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);

        colors[ImGuiCol_MenuBarBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.38f, 0.38f, 0.38f, 1.0f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 0.5f, 0.9f, 1.0f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.25f, 0.5f, 0.9f, 1.0f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.20f, 0.45f, 0.85f, 1.0f);
        colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);

        // Tabs like VS2022
        colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_TabActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.0f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.0f);

        // Separator
        colors[ImGuiCol_Separator] = ImVec4(0.29f, 0.29f, 0.29f, 1.0f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.0f);

        // Tooltip
        colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);

        // Optional: scrollbar rounding 0 to mimic VS
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
    }

    void Styles::LightMode() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // --- Rounding -- 
        style.WindowRounding = 0.0f;
        style.FrameRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
        style.TabRounding = 0.0f;

        // --- Padding ---
        style.FramePadding = ImVec2(6, 4);
        style.ItemSpacing = ImVec2(6, 4);

        // --- Borders & separators ---
        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.TabBorderSize = 1.0f;
        style.SeparatorTextBorderSize = 1.0f;

        // --- Colors ---
        colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.0f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.0f);
        colors[ImGuiCol_Border] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.0f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.96f, 0.96f, 0.96f, 1.0f);

        colors[ImGuiCol_MenuBarBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.78f, 0.78f, 0.78f, 1.0f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.73f, 0.73f, 0.73f, 1.0f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 0.5f, 0.9f, 1.0f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.25f, 0.5f, 0.9f, 1.0f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.2f, 0.45f, 0.85f, 1.0f);
        colors[ImGuiCol_Button] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.0f);

        // Tabs like VS2022
        colors[ImGuiCol_Tab] = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
        colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.0f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.94f, 0.94f, 0.94f, 1.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
        colors[ImGuiCol_Header] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.0f);

        // Separator
        colors[ImGuiCol_Separator] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.85f, 0.85f, 0.85f, 1.0f);

        // Tooltip
        colors[ImGuiCol_PopupBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.0f);

        // Optional: scrollbar rounding 0 to mimic VS
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
    }
}

