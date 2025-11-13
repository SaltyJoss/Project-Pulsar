
#include "pch.h"
#include "Scene/Input.h"
#include <GLFW/glfw3.h>

#include "EngineLib/LogMacros.h"

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

bool Input::IsKeyPressed(GLFWwindow* window, int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(GLFWwindow* window, eInputButton button)
{
    int glfwButton;
    switch (button) {
    case eInputButton::Left:
        glfwButton = GLFW_MOUSE_BUTTON_LEFT;
        break;
    case eInputButton::Right:
        glfwButton = GLFW_MOUSE_BUTTON_RIGHT;
        break;
    case eInputButton::Middle:
        glfwButton = GLFW_MOUSE_BUTTON_MIDDLE;
        break;
    default:
        return false;
    }
    return glfwGetMouseButton(window, glfwButton) == GLFW_PRESS;
}