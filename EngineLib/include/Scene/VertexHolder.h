#pragma once
#include "EngineCore.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace elements {
	class ENGINE_API VertexHolder {
	public:
		VertexHolder() : _pos(), _normal() {}

		VertexHolder(const std::vector<std::string> tokens) {}

		VertexHolder(const glm::vec3& pos, const glm::vec3& normal) : _pos(pos), _normal(normal) {}

		~VertexHolder() = default;

		glm::vec3 _pos;
		glm::vec3 _normal;
	};
}
