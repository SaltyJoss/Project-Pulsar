#pragma once

#include "EngineLib/Export.h"
#include <memory>
#include <string>

// forward declarations
namespace window { class GLWindow; }
namespace elements { class Camera; }

class ENGINE_API Application {
public:
	Application(const std::string& name);

	~Application();

	static Application& Instance() { return *sInstance; }

	void run();

private:
	static Application* sInstance;

	std::unique_ptr<window::GLWindow> _window;
	std::unique_ptr<elements::Camera> _camera;
};