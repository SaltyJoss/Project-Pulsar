#pragma once

#include "Platform/Window.h"

#include "Rendering/GUIContext.h"
#include "Rendering/OpenGLContext.h"
#include "Rendering/OpenGLBufferManager.h"

#include "Scene/SceneView.h"
#include "Scene/DebugPanel.h"
#include "Scene/ControlPanel.h"

#include "Scene/Camera.h"
#include "Scene/Light.h"
#include "Scene/Mesh.h"
#include "Rendering/ShaderUtil.h"

using namespace render;
using namespace gui;
using namespace elements;
using namespace shaders;

/*class WindowManager {
private:
    GLFWwindow* _window;
    int lastX, lastY, lastW, lastH;
    bool isMaximised = false;

public:

    void SetupWindow(GLFWwindow* window) { _window = window; }
    ~WindowManager() = default;

    GLFWwindow* GetWindow() const { return _window; }

    void Render();

};*/

extern Debug gLog; // Global Variable for debugging and logs

namespace window {
    class GLWindow : public IWindow {
    public:
        GLWindow() : _isRunning(true), _window(nullptr) {
            _GUICntx = std::make_unique<GUIContext>();
            _renderCntx = std::make_unique<OpenGLContext>();
        }

        ~GLWindow();

        bool init(int width, int height, const std::string& header);
        void render();
        void inputHandler();
        void* getNativeWin() override { return _window; }
        void setNativeWin(void* window) { _window = (GLFWwindow*)window; }

        void onScroll(double delta) override;
        void onKey(int key, int scancode, int action, int mods) override;
        void onResize(int width, int height) override;
        void onClose() override;
        bool isRunning() { return _isRunning; }

    private:
        bool _isRunning;

        GLFWwindow* _window;

        std::unique_ptr<GUIContext> _GUICntx;
        std::unique_ptr<OpenGLContext> _renderCntx;

        std::unique_ptr<SceneView> _sceneView;
        std::unique_ptr<ControlPanel> _controlPanel;
        std::unique_ptr<DebugPanel> _debugPanel;
    };
}