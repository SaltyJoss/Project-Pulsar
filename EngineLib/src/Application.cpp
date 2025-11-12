#include "pch.h"
#include "Application.h"

#include "Platform/WindowManager.h"
#include "Scene/Camera.h"
#include "Platform/Window.h"

Application* Application::sInstance = nullptr;

Application::Application(const std::string& appName) {
	_window = std::make_unique<window::GLWindow>();
	_window->init(1920, 1080, appName);
}

Application::~Application() = default;

void Application::run() {
	while (_window->isRunning() && !_window->shouldClose()) {
		_window->pollEvents();
		_window->render();
		_window->swapBuffers();
	}
}