#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

namespace elements {
	enum class eInputButton {
		Left = 0,
		Right = 1,
		Middle = 2,
		None = 9
	};

	class Input {
	public:
		static eInputButton GetPressedButton(GLFWwindow* window);

	private:
		Input() = default;
	};
	
}