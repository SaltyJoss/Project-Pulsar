#pragma once
#include "EngineCore.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "Scene/Element.h"
#include "Rendering/ShaderUtil.h"
#include "Scene/Input.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace elements {
	class ENGINE_API Camera : public Element
	{
	public:

		Camera(const glm::vec3& position, float fov, float aspect, float zNear, float zFar) {
			_position = position;
			_aspect = aspect;
			_near = zNear;
			_far = zFar;
			_FOV = fov;

			setAspect(_aspect);
			updateViewMatrix();
		}

		void update(shaders::Shader* shader) override {
			glm::mat4 model{ 1.0f };
			shader->setMat4(model, "model");
			shader->setMat4(_viewMatrix, "view");
			shader->setMat4(getProjection(), "projection");
			shader->setVec3(_position, "camPos");
		}


		const glm::mat4& getProjection() const { return _projection; }
		glm::vec2 getCurrentPos2D() const { return _currentPos2D; }
		glm::vec3 getPosition() const { return _position; }
		glm::mat4 getViewProjection() const { return _projection * getViewMatrix(); }
		glm::vec3 getUp() const { return glm::rotate(getDirection(), _up); }
		glm::vec3 getRight() const { return glm::rotate(getDirection(), _right); }
		glm::vec3 getForward() const { return glm::rotate(getDirection(), _forward); }
		glm::quat getDirection() const { return glm::quat(glm::vec3(-_pitch, -_yaw, 0.0f)); }
		glm::mat4 getViewMatrix() const { return _viewMatrix; }

		void setAspect(float aspect) { _projection  = glm::perspective(_FOV, aspect, _near, _far); }
		void setFocus(const glm::vec3& focus) { _focus = focus; updateViewMatrix(); }
		void setCurrentPos2D(const glm::vec2& pos) { _currentPos2D = pos; }
		void setYaw(float yaw) { _yaw = yaw; updateViewMatrix(); }
		void setPitch(float pitch) { _pitch = pitch; updateViewMatrix(); }
		void setFOV(float FOV) { _FOV = FOV; }

		void setDistance(float offset) {
			_distance += offset;
			updateViewMatrix();
		}

		void reset()
		{
			_focus = { 0.0f, 0.0f, 0.0f };
			//_distance = 5.0f;
			updateViewMatrix();
		}

		void onMouseWheel(double delta) {
			setDistance(delta * 0.5f);
			updateViewMatrix();
		}

		void onMouseMove(double x, double y, eInputButton button) {
			glm::vec2 pos2d{ x, y };

			if (button == eInputButton::Right) {
				glm::vec2 delta = (pos2d - _currentPos2D) * 0.004f;

				float sign = getUp().y < 0 ? -1.0f : 1.0f;

				_yaw += sign * delta.x * _rotationSpeed;
				_pitch += delta.y * _rotationSpeed;

				updateViewMatrix();
			}
			else if (button == eInputButton::Left) {
				glm::vec2 delta = (pos2d - _currentPos2D) * 0.003f;

				_focus += -getRight() * delta.x * _distance;
				_focus += getUp() * delta.y * _distance;

				updateViewMatrix();
			}

			_currentPos2D = pos2d;
		}

		void updateViewMatrix() {
			_position = _focus - getForward() * _distance;

			glm::quat orientation = getDirection();
			_viewMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(orientation);
			_viewMatrix = glm::inverse(_viewMatrix);
		}

		void moveForward(float delta);
		void moveBackward(float delta);
		void moveLeft(float delta);
		void moveRight(float delta);

		void processKeyboard(int key, float delta);
		void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	private:
		glm::mat4 _viewMatrix;
		glm::mat4 _projection  = glm::mat4{ 1.0f };

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _focus = { 0.0f, 0.0f, 0.0f };

		float _distance = 5.0f;
		float _aspect;
		float _FOV;
		float _near;
		float _far;
		float _pitch = 0.0f;
		float _yaw = 0.0f;

		glm::vec2 _currentPos2D = { 0.0f, 0.0f };
		const glm::vec3 _right = { 1.0f, 0.0f, 0.0f };
		const glm::vec3 _up = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 _forward = { 0.0f, 0.0f, -1.0f };

		const float _rotationSpeed = 2.0f;

	};
}