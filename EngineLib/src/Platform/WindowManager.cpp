
#include "pch.h"
#ifdef __gl_h_
#undef __gl_h_
#endif
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

#include "EngineLib/LogMacros.h"


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


    bool GLWindow::shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

    void GLWindow::pollEvents() {
        glfwPollEvents();
    }

    void GLWindow::swapBuffers() {
        glfwSwapBuffers(_window);
    }



    void* window::GLWindow::getNativeWin() {
        return _window;
    }

    void window::GLWindow::setNativeWin(void* window) {
        _window = static_cast<GLFWwindow*>(window);
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

/*
 * --------------------------------------------
 *				USER INTERACTIONS
 * --------------------------------------------
 */
    void window::GLWindow::onScroll(double delta) {
        if (_sceneView)
            _sceneView->onMouseWheel(delta);
    }

    void GLWindow::onKey(int key, int scancode, int action, int mods) {
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {}
        if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {}
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {}
        if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {}

        if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {}
    }

/*
 * --------------------------------------------
 *				WINDOW STATES
 * --------------------------------------------
 */

    bool GLWindow::isRunning() const {
        return _isRunning;
    }

    void GLWindow::onClose() {
        _isRunning = false;
    }
}
