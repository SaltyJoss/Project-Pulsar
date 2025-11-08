#pragma once

#include "ch.h"

namespace elements {
	enum class eInputButton {
	// Mouse Buttons
		Left = 0,
		Right = 1,
		Middle = 2,
		None = 9
	};

	class Input {
	public:
		static eInputButton GetPressedButton(GLFWwindow* window) {
			eInputButton result = eInputButton::None;

			if (glfwGetMouseButton(window, 0)	   == GLFW_PRESS)	{ return eInputButton::Left; }
			else if (glfwGetMouseButton(window, 1) == GLFW_PRESS)	{ return eInputButton::Right; }
			else if (glfwGetMouseButton(window, 2) == GLFW_PRESS)	{ return eInputButton::Middle; }

			return eInputButton::None;
		}
	};
	
}