#include "pch.h"
#include "Application.h"

#include "Platform/WindowManager.h"
#include "Scene/Camera.h"
#include "Platform/Window.h"

Application* Application::sInstance = nullptr;

Application::Application(const std::string& appName) {
	_window = std::make_unique<window::GLWindow>();
	_window->init(1280, 720, appName);
}

Application::~Application() = default;

void Application::run() {
	while (_window->isRunning() && !_window->shouldClose()) {
		_window->render();
	}
}