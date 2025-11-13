#pragma once
#include "EngineCore.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Scene/Element.h"
#include "Rendering/ShaderUtil.h"
#include "Scene/Input.h"
#include "Scene/Mesh.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace elements {
	class ENGINE_API Object : public Element
	{
	public:
		Object(std::shared_ptr<elements::Mesh> mesh) : _mesh(mesh), _position(0.0f), _rotation(0.0f), _distance(5.0f), _lastMousePos(0.0f) {}

		void reset() {
			_position = { 0.0f, 0.0f, 0.0f };
			_rotation = { 0.0f, 0.0f, 0.0f };
			applyTransformToMesh();

		}

		void onMouseWheel(double delta) { _distance += delta * 0.5f; }

		void onMouseMove(double x, double y, eInputButton button) {
			glm::vec2 pos2d{ x, y };
			glm::vec2 delta = pos2d - _lastMousePos;
			_lastMousePos = pos2d;

			if (button == eInputButton::Right) {
				delta *= 0.004f;
				_rotation.x += -delta.y;
				_rotation.y += delta.x;

				applyTransformToMesh();
			}
			else if (button == eInputButton::Left) {
				delta *= 0.003f;
				_position += glm::vec3(delta.x * _distance, -delta.y * _distance, 0.0f);

				applyTransformToMesh();
			}

		}

		void applyTransformToMesh() {
			if (!_mesh) return;
			_mesh->_position = _position;
			_mesh->_rotation = _rotation;
		}

		std::shared_ptr<Mesh> getMesh() { return _mesh; }
		void setLastMousePos(const glm::vec2& pos) { _lastMousePos = pos; }
		glm::vec2 getLastMousePos() const { return _lastMousePos; }

		void update(shaders::Shader* shader) override {
			if (_mesh) { _mesh->update(shader); }
		}

	private:
		std::shared_ptr<elements::Mesh> _mesh;

		glm::mat4 _modelMatrix;
		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };

		float _distance = 5.0f;

		const float _rotationSpeed = 2.0f;

		glm::vec2 _lastMousePos;

	};
}