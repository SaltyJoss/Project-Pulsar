#pragma once
#include "EngineCore.h"

#include "RenderBase.h"
#include "Scene/Styles.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace render {
	class ENGINE_API OpenGLContext : public RenderContext {
	public:
		bool init(window::IWindow* window) override;
		void preRender() override;
		void postRender() override;
		void end() override;

		GLFWwindow* getGLFWWindow() const { return _glfwWindow; }

	private:
		GLFWwindow* _glfwWindow = nullptr;
	};
}