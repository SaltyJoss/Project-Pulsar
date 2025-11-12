#pragma once

#include "EngineCore.h"
#include "EngineLib/Export.h"

#include <imgui.h>

//Basic window interface
namespace window {
    class ENGINE_API IWindow {
    public:
        virtual bool init(int width, int height, const std::string& title) = 0;

        // Core windowing
        virtual bool isRunning() const = 0;
        virtual bool shouldClose() const = 0;
        virtual void pollEvents() = 0;
        virtual void swapBuffers() = 0;

        // Native window access
        virtual void* getNativeWin() = 0;
        virtual void setNativeWin(void* window) = 0;

        // Callbacks
        virtual void onKey(int key, int scancode, int action, int mods) = 0;
        virtual void onScroll(double delta) = 0;
        virtual void onResize(int width, int height) = 0;
        virtual void onClose() = 0;

        virtual ~IWindow() = default;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual const std::string& getHeader() const = 0;
    };
}