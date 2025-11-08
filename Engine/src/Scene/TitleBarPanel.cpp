/*
 NOT CURRENT USED IN THE PROJECT


#include "ResourceManager.h"
#include "TitleBarPanel.h"

TitleBarPanel::TitleBarPanel(WindowManager* wm) : windowManager(wm) {}

void TitleBarPanel::InitIcons() {
	iconMinimiseTex = ResourceManager::GetTexture("minimise");
	iconMaximiseTex = ResourceManager::GetTexture("maximise");
	iconCloseTex    = ResourceManager::GetTexture("close");
}

TitleBarPanel::TitleBarPanel() : windowManager(nullptr), iconMinimiseTex(0), iconMaximiseTex(0), iconCloseTex(0) {}

void TitleBarPanel::Render(float height) {

	ImVec2 winSize = ImGui::GetWindowSize();
	ImGui::BeginChild("Sim", ImVec2(winSize.x, height), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	float buttonSize = height * 0.5f;
    float padding = 5.0f;
    float totalWidth = 3 * buttonSize + 2 * padding; // 3 buttons + 2 spaces
    ImGui::SetCursorPosX(winSize.x - totalWidth - 40);

    DrawMinimiseButton(buttonSize);
    ImGui::SameLine(0, padding);
    DrawMaximiseButton(buttonSize);
    ImGui::SameLine(0, padding);
    DrawCloseButton(buttonSize);

	ImGui::EndChild();

}

void TitleBarPanel::DrawMinimiseButton(float size) {
    if (ImGui::ImageButton("minimise", (ImTextureID)(intptr_t)iconMinimiseTex,
        ImVec2(size, size))) {
        windowManager->Minimise();
    }
}

void TitleBarPanel::DrawMaximiseButton(float size) {
    if (ImGui::ImageButton("maximise", (ImTextureID)(intptr_t)iconMaximiseTex,
        ImVec2(size, size))) {
        windowManager->ToggleMaximise();
    }
}

void TitleBarPanel::DrawCloseButton(float size) {
    if (ImGui::ImageButton("close", (ImTextureID)(intptr_t)iconCloseTex,
        ImVec2(size, size))) {
        GLFWwindow* window = windowManager->GetWindow();  // Access the main GLFW window
        glfwSetWindowShouldClose(window, true); 
    }
}*/
