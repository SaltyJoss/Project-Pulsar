#pragma once
#include "EngineCore.h"

#include <GLFW/glfw3.h>
#include <cstdint>
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace elements {
	enum class eInputButton {
		Left = 0,
		Right = 1,
		Middle = 2,
		None = 9
	};

	class ENGINE_API Input {
	public:
		static eInputButton GetPressedButton(GLFWwindow* window);

	private:
		Input() = default;
	};
	
}