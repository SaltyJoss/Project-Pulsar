
#include "pch.h"

#ifdef __gl_h_
#undef __gl_h_
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/Camera.h"

#include "EngineLib/LogMacros.h"

namespace elements {

	void Camera::processKeyboard(int key, float delta) {
		float velocity = delta;
		if (key == GLFW_KEY_W)
			moveForward(velocity);
		if (key == GLFW_KEY_S)
			moveBackward(velocity);
		if (key == GLFW_KEY_A)
			moveLeft(velocity);
		if (key == GLFW_KEY_D)
			moveRight(velocity);
		updateViewMatrix();
	}

	void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
		const double sensitivity = 0.001f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		_yaw += xoffset;
		_pitch += yoffset;

		if (constrainPitch) {
			if (_pitch > glm::radians(89.0f))
				_pitch = glm::radians(89.0f);
			if (_pitch < glm::radians(-89.0f))
				_pitch = glm::radians(-89.0f);
		}
		updateViewMatrix();
	}

	void Camera::moveForward(float delta) {
		_focus += getForward() * delta;
	}

	void Camera::moveBackward(float delta) {
		_focus -= getForward() * delta;
	}

	void Camera::moveLeft(float delta) {
		_focus -= getRight() * delta;
	}

	void Camera::moveRight(float delta) {
		_focus += getRight() * delta;
	}
}