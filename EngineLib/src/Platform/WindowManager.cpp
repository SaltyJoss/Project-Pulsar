
#include "pch.h"
#include <glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/Window.h"

#include "Rendering/GUIContext.h"
#include "Rendering/OpenGLContext.h"
#include "Rendering/OpenGLBufferManager.h"
#include "Rendering/ShaderUtil.h"

#include "Scene/SceneView.h"
#include "Scene/DebugPanel.h"
#include "Scene/ControlPanel.h"

#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Scene/Input.h"
#include "Scene/Mesh.h"

#include "Platform/WindowManager.h"


namespace window {
    GLWindow::GLWindow() {
        _header = new std::string();
    }

    GLWindow::~GLWindow() { 
        _renderCntx->end();
        _GUICntx->end();
        
        if (_window) { glfwDestroyWindow(_window); }

        glfwTerminate();
        delete _header;

        LOG_INFO("GLWindow destroyed, rendering and GUI contexts ended");
    }

    void GLWindow::render() {
        _renderCntx->preRender();
        _GUICntx->preRender();

        if (_sceneView)     _sceneView->render();
        if (_controlPanel)  _controlPanel->render(_sceneView.get());
        if (_debugPanel)    _debugPanel->render();

        _GUICntx->postRender();
        _renderCntx->postRender();
    }

    bool GLWindow::init(int width, int height, const std::string& header) {
        _width = width;
        _height = height;
        *_header = header;

        if (!glfwInit()) {
            LOG_ERROR("GLFW init failed");
            _isRunning = false;
            return false;
        }

        // GLFW minimum OpenGL config
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create the window
        _window = glfwCreateWindow(_width, _height, _header->c_str(), nullptr, nullptr);
        if (!_window) {
            LOG_ERROR("Failed to create GLFW window");
            glfwTerminate();
            _isRunning = false;
            return false;
        }

        glfwMakeContextCurrent(_window);

        // Load GL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_ERROR("Failed to load GLAD");
            _isRunning = false;
            return false;
        }

        // Context layers
        _renderCntx = std::make_unique<render::OpenGLContext>();
        _renderCntx->init(this);

        _GUICntx = std::make_unique<render::GUIContext>();
        _GUICntx->init(this);

        // UI + scene
        _sceneView = std::make_unique<gui::SceneView>();
        _controlPanel = std::make_unique<gui::ControlPanel>(_sceneView.get());
        _debugPanel = std::make_unique<gui::DebugPanel>();

        _controlPanel->setMeshLoadCallback([this](std::string path)
            {
                _sceneView->loadMesh(path);
                LOG_INFO("Mesh loaded: %s", path.c_str());
            }
        );

        _isRunning = true;
        return true;
    }

    void GLWindow::onResize(int width, int height) {
        _width = width;
        _height = height;
        LOG_INFO("Window resized: Width=%d, Height=%d", width, height);

        _sceneView->resize(_width, _height);
        LOG_INFO("SceneView resized");
        render();
    }

    bool GLWindow::isRunning() const {
        return _isRunning;
    }

    bool GLWindow::shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void GLWindow::pollEvents() {
        glfwPollEvents();
    }

    void GLWindow::swapBuffers() {
        glfwSwapBuffers(_window);
    }

    void GLWindow::onKey(int key, int scancode, int action, int mods) {
		// Will handle key events here
    }

    void GLWindow::onClose() {
        _isRunning = false;
    }

    void* window::GLWindow::getNativeWin() {
        return _window;
    }

    void window::GLWindow::setNativeWin(void* window) {
        _window = static_cast<GLFWwindow*>(window);
    }

    void window::GLWindow::onScroll(double delta) {
        if (_sceneView)
            _sceneView->onMouseWheel(delta);
    }

    int window::GLWindow::getWidth() const {
        return _width;
    }

    int window::GLWindow::getHeight() const {
        return _height;
    }

    const std::string& window::GLWindow::getHeader() const {
        return *_header;
    }

}
