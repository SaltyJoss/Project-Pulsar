#include "pch.h"

#include "Application.h"
#include "Platform/WindowManager.h"

Application::Application(const std::string& appName) {
	_window = std::make_unique<window::GLWindow>();
	_window->init(1920, 1080, appName);
}

void Application::run() {
	while (_window->isRunning()) { _window->render(); }
}