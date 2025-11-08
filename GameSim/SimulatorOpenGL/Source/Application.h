#pragma once

#include "Window/GUIManager.h"
#include "Window/WindowManager.h"
#include "Elements/Camera.h"

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
