#pragma once
#include "EngineCore.h"

#include "Rendering/ShaderUtil.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace elements {
	class ENGINE_API Element {
	public:
		virtual void update(shaders::Shader* shader) = 0;
	};
}