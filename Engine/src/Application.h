#pragma once

#include "Platform/GUIManager.h"
#include "Platform/WindowManager.h"
#include "Scene/Camera.h"

class Application
{

public:
	Application(const std::string& name);

	static Application& Instance() { return *sInstance; }

	void run();

	/*bool Init();
	void Run();
	void Shutdown();*/

private:
	static Application* sInstance;

	std::unique_ptr<window::GLWindow> _window;

	/*std::unique_ptr<GUIManager> gui;
	WindowManager windowManager;
	GLFWwindow* window = nullptr;
	std::unique_ptr<SimulationManager> simulation;*/
};
