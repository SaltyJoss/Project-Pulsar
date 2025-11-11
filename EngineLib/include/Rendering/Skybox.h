#pragma once

#include "EngineCore.h"

#include "Rendering/ShaderUtil.h"
#include "Rendering/Cubemap.h"

namespace render {
	class Skybox {
	public:
		Skybox(Cubemap* cubemap, shaders::Shader* shader);

		void render(const glm::mat4& view, const glm::mat4& proj);

	private:
		unsigned int _VAO, _VBO, _EBO;
		
		Cubemap* _cubemap;
		shaders::Shader* _shader;
	};
}