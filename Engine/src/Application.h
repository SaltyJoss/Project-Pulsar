#pragma once

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
};
