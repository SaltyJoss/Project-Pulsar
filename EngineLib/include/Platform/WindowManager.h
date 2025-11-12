#pragma once
#include "EngineCore.h"

#include "Platform/Window.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

// forward declares
struct GLFWwindow;

namespace render { 
    class GUIContext; 
    class OpenGLContext; 
}
namespace gui { 
    class SceneView; 
    class ControlPanel; 
    class DebugPanel; 
}

namespace window {
    class ENGINE_API GLWindow : public IWindow {
    public:
        GLWindow();
        ~GLWindow();

        bool init(int width, int height, const std::string& title) override;

        // IWindow interface
        bool isRunning() const override;
        bool shouldClose() const override;
        void pollEvents() override;
        void swapBuffers() override;

        void* getNativeWin() override;
        void setNativeWin(void* window) override;

        int getWidth() const override;
        int getHeight() const override;
        const std::string& getHeader() const override;

        void onKey(int key, int scancode, int action, int mods) override;
        void onScroll(double delta) override;
        void onResize(int width, int height) override;
        void onClose() override;

        void render();

    private:
        bool _isRunning = true;
        GLFWwindow* _window = nullptr;

        std::unique_ptr<render::GUIContext> _GUICntx;
        std::unique_ptr<render::OpenGLContext> _renderCntx;

        std::unique_ptr<gui::SceneView> _sceneView;
        std::unique_ptr<gui::ControlPanel> _controlPanel;
        std::unique_ptr<gui::DebugPanel> _debugPanel;

        int _width = 0;
        int _height = 0;
        std::string *_header;
    };
}