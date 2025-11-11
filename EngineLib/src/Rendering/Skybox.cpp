
#include "pch.h"

#include "Rendering/Skybox.h"

static const float skyboxVertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

static unsigned int skyboxIndices[] = {
	// RIGHT
	1, 2, 0,
	6, 5, 1,
	// LEFT
	0, 4, 7,
	7, 3, 0,
	// TOP
	4, 5, 6,
	6, 7, 4,
	// BOTTOM
	0, 3, 2,
	2, 1, 0,
	// BACK
	0, 1, 5,
	5, 4, 0,
	// FRONT
	3, 7, 6,
	6, 2, 3
};

namespace render {
	Skybox::Skybox(Cubemap* cubemap, shaders::Shader* shader)
		: _cubemap(cubemap)
		, _shader(shader)
	{
		LOG_INFO("Building skybox VAO");

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_EBO);
		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		LOG_INFO("Skybox VAO=%u VBO=%u EBO=%u", _VAO, _VBO, _EBO);
	}

	void Skybox::render(const glm::mat4& view, const glm::mat4& proj) {
		LOG_INFO_ONCE("Skybox draw entered");
		glm::mat4 viewNoTrans = glm::mat4(glm::mat3(view));

		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_FALSE);
		_shader->use();
		_shader->setMat4(viewNoTrans, "view");
		_shader->setMat4(proj, "projection");
		_cubemap->bind(0);
		_shader->setInt1(0, "skybox");

		glBindVertexArray(_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
	}
}