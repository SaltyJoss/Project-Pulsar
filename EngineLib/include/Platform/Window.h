#pragma once

#include "EngineCore.h"

#include <imgui.h>

//Basic window interface
namespace window {
class IWindow {
public:
	virtual void* getNativeWin() = 0;
	virtual void setNativeWin(void* window) = 0;

	virtual void onKey(int  key, int scancode, int action, int mods) = 0;
	virtual void onScroll(double delta) = 0;
	virtual void onResize(int width, int height) = 0;
	virtual void onClose() = 0;

	int _width = 0;
	int _height = 0;
	std::string _header = "";

	ImVec2 _winSize;
	ImVec2 _padding;
};
}