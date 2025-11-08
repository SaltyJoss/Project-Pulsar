
/*#include "WindowManager.h"
#include "GUIManager.h"

GUIManager::GUIManager(WindowManager* manager) : windowManager(manager) {}

void GUIManager::BeginFrame() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

// End Framew Method
void GUIManager::EndFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Draw Panel method 
void GUIManager::DrawPanel() {
	ImGuiWindowFlags panelFlags  =	
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoScrollbar;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(33, 33, 33, 255));
	ImGui::Begin("Robotic-Arm Simualtor V0.0", nullptr, panelFlags);

	winSize = ImGui::GetIO().DisplaySize;
	padding = ImGui::GetStyle().WindowPadding;
	debugHeight = 300.0f;
	ctrlPanelWidth = 400.0f;

	ContainerPanel();

	ImGui::End();
	//ImGui::PopStyleColor();
}

void GUIManager::ContainerPanel() {
	if (!titleBar)
		titleBar = std::make_unique<TitleBarPanel>(windowManager);
	titleBar->Render(30.0f);

	ctrlPanel.Render(winSize, padding, debugHeight, ctrlPanelWidth);
	ImGui::SameLine();
	simPanel.Render(winSize, padding, debugHeight, ctrlPanelWidth, simulation.get());
	debug.Render(winSize, padding, debugHeight, ctrlPanelWidth);
}

void GUIManager::InitResources() {
	styles.DarkMode();
	ResourceManager::LoadTexture("close", "assets/close.png");
	ResourceManager::LoadTexture("minimise", "assets/minimise.png");
	ResourceManager::LoadTexture("maximise", "assets/maximise.png");
}
*/