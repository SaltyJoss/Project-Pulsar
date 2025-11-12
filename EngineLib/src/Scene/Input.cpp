
#include "pch.h"
#include "Scene/Input.h"
#include <GLFW/glfw3.h>

using namespace elements;

eInputButton Input::GetPressedButton(GLFWwindow* window)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        return eInputButton::Left;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        return eInputButton::Right;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        return eInputButton::Middle;

    return eInputButton::None;
}