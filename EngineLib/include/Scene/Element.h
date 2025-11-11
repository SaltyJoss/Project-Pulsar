#pragma once

#include "EngineCore.h"

#include "Rendering/ShaderUtil.h"

namespace elements {
	class Element {
	public:
		virtual void update(shaders::Shader* shader) = 0;
	};
}