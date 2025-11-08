#include "ch.h"

#include "WindowManager.h"
#include "Elements/Input.h"

namespace window {
    GLWindow::~GLWindow() { _renderCntx->end(); _GUICntx->end(); LOG_INFO("GLWindow destroyed, rendering and GUI contexts ended");}

    bool GLWindow::init(int width, int height, const std::string& header) {
        _width = width;
        _height = height;
        _header = header;
        LOG_INFO("Initializing GLWindow: Width=%d, Height=%d, Header=%s", width, height, header.c_str());

        _renderCntx->init(this);
        _GUICntx->init(this);
        LOG_INFO("Render context initialized");

        _winSize = ImGui::GetIO().DisplaySize;
        _padding = ImGui::GetStyle().WindowPadding;
        LOG_INFO("GUI context initialized");

        _sceneView = std::make_unique<SceneView>();
        _controlPanel = std::make_unique<ControlPanel>(_sceneView.get());
        _debugPanel = std::make_unique<DebugPanel>();
        LOG_INFO("SceneView, ControlPanel, DebugPanel created");

        _controlPanel->setMeshLoadCallback([this](std::string path) { _sceneView->loadMesh(path); LOG_INFO("Mesh load callback triggered for path: %s", path.c_str()); });

        return _isRunning;
    }

    void GLWindow::render() {
        _renderCntx->preRender();
        _GUICntx->preRender();

        _sceneView->render();
        _controlPanel->render(_sceneView.get());
        _debugPanel->render();

        _GUICntx->postRender();
        _renderCntx->postRender();

        inputHandler();
    }

    void GLWindow::onResize(int width, int height) {
        _width = width;
        _height = height;
        LOG_INFO("Window resized: Width=%d, Height=%d", width, height);

        _sceneView->resize(_width, _height);
        LOG_INFO("SceneView resized");
        render();
    }

    void GLWindow::inputHandler() {
        if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) { _sceneView->onMouseWheel(-0.4f); }
        if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) { _sceneView->onMouseWheel(0.4f); }
        if (glfwGetKey(_window, GLFW_KEY_F) == GLFW_PRESS) { _sceneView->resetView(); }

        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        _sceneView->onMouseMove(x, y, Input::GetPressedButton(_window));
    }

    void GLWindow::onScroll(double delta) { _sceneView->onMouseWheel(delta); }
    void GLWindow::onKey(int key, int scancode, int action, int mods) { if (action == GLFW_PRESS) {} }
    void GLWindow::onClose() { _isRunning = false; LOG_WARN("Window closed, stopping main loop"); }
}
