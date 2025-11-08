#pragma once

#include "Shader/ShaderUtil.h"

namespace elements {
	class Element {
	public:
		virtual void update(shaders::Shader* shader) = 0;
	};
}