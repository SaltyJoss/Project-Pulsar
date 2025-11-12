
#include "pch.h"
#include <glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/OpenGLContext.h"

namespace render {
	static void onKey_Callback(GLFWwindow* win, int  key, int scancode, int action, int mods) {
		auto currentWindow = static_cast<window::IWindow*>(glfwGetWindowUserPointer(win));
		currentWindow->onKey(key, scancode, action, mods);
	}

	static void onScroll_Callback(GLFWwindow* win, double xoffset, double yoffset) {
		auto currentWindow = static_cast<window::IWindow*>(glfwGetWindowUserPointer(win));
		currentWindow->onScroll(yoffset);
	}

	static void onResize_Callback(GLFWwindow* win, int width, int height) {
		auto currentWindow = static_cast<window::IWindow*>(glfwGetWindowUserPointer(win));
		currentWindow->onResize(width, height);
	}

	static void onClose_Callback(GLFWwindow* win) {
		window::IWindow* currentWindow = static_cast<window::IWindow*>(glfwGetWindowUserPointer(win));
		currentWindow->onClose();
	}

	bool render::OpenGLContext::init(window::IWindow* window) {
		LOG_INFO("init() Called!");
		__super::init(window);

		if (!window->getWidth() || !window->getHeight()) {
			LOG_ERROR("Window dimensions not set!");
			return false;
		}

		if (!glfwInit()) { 
			LOG_ERROR("Failed to initialize GLFW -> ", glfwGetError(NULL));
			return false; 
		}

		auto glWindow = glfwCreateWindow(window->getWidth(), window->getWidth(), window->getHeader().c_str(), nullptr, nullptr);
		window->setNativeWin(glWindow);

		if (!glWindow) { 
			gLog.logError("OpenGL", "Failed to create GLFW window: ", glfwGetError(NULL));
			LOG_ERROR("Failed to create GLFW window -> ", glfwGetError(NULL));
			glfwTerminate();
			return false;
		}

		glfwSetWindowUserPointer(glWindow, window);
		glfwSetKeyCallback(glWindow, onKey_Callback);
		glfwSetScrollCallback(glWindow, onScroll_Callback);
		glfwSetWindowSizeCallback(glWindow, onResize_Callback);
		glfwSetWindowCloseCallback(glWindow, onClose_Callback);
		glfwMakeContextCurrent(glWindow);

		GLenum err = glewInit();
		if (err != GLEW_OK) { 
			LOG_ERROR("GLEW failed -> ", glewGetErrorString(err));
			return false; 
		}

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
			LOG_ERROR("Failed to initialise GLAD");
			return false; 
		}

		glEnable(GL_DEPTH_TEST);
		LOG_INFO("GL_DEPTH_TEST enabled");

		return true;
	}

	void render::OpenGLContext::preRender() {
		glViewport(0, 0, _window->getWidth(), _window->getHeight());
		glClearColor(0.33f, 0.33f, 0.33f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void render::OpenGLContext::postRender() {
		glfwPollEvents();
		glfwSwapBuffers((GLFWwindow*)_window->getNativeWin());
	}

	void render::OpenGLContext::end() {
		glfwDestroyWindow((GLFWwindow*)_window->getNativeWin());
		glfwTerminate();
		LOG_INFO("GLFW window destroyed and context terminated successfully.");
	}
}
