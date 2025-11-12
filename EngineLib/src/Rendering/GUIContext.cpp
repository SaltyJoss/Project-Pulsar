
#include "pch.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Rendering/GUIContext.h"

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace render {
	bool render::GUIContext::init(window::IWindow* window) {
		__super::init(window);

		const char* glslVersion = "#version 410";

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard
					   |  ImGuiConfigFlags_DockingEnable
					   |  ImGuiConfigFlags_ViewportsEnable;

		_style = std::make_unique<gui::Styles>();
		_style->DarkMode();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)_window->getNativeWin(), true);
		ImGui_ImplOpenGL3_Init(glslVersion);

		LOG_INFO("ImGui context initialized (GLSL %s)", glslVersion);
		return true;
	}

	void render::GUIContext::preRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking  | ImGuiWindowFlags_NoTitleBar 
									 | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize 
									 | ImGuiWindowFlags_NoMove	   | ImGuiWindowFlags_NoBringToFrontOnFocus 
									 | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Invisible-Window", nullptr, windowFlags);
		ImGui::PopStyleVar(3);

		ImGuiID dockingSpaceID = ImGui::GetID("Invisible-Window-Docking-Space");

		ImGui::DockSpace(dockingSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();

		LOG_INFO_ONCE("ImGui preRender frame prepared with docking space ID %u", dockingSpaceID);
	}

	void render::GUIContext::postRender() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);

			LOG_INFO_ONCE("ImGui platform windows rendered (viewports enabled)");
		}
	}

	void render::GUIContext::end() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		LOG_INFO("ImGui context shutdown completed");
	}
}