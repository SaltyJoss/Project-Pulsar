
#include "pch.h"

#ifdef __gl_h_
#undef __gl_h_
#endif
#include <glad/glad.h>

#include "Rendering/Cubemap.h"
#include <stb/stb_image.h>

#include "EngineLib/LogMacros.h"

namespace render{
	Cubemap::Cubemap(const std::array<std::string, 6>& faces) {
		glGenTextures(1, &_cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);

		LOG_INFO("Loading cubemap…");
		for (unsigned int i = 0; i < faces.size(); i++) {
			int width, height, channels;
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);

			LOG_INFO("Loaded face[%d] \"%s\" (%dx%d, channels=%d)", i, faces[i].c_str(), width, height, channels);

			if (data) {
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB,
					GL_UNSIGNED_BYTE, data
				);
				stbi_image_free(data);
			}
			else {
				LOG_ERROR("failed to load face: %s", faces[i]);
				stbi_image_free(data);
			}
		}
		LOG_INFO("Cubemap creation finished");

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Cubemap::~Cubemap()
	{
		// Delete GL texture if needed
		if (_cubemapTexture != 0) {
			glDeleteTextures(1, &_cubemapTexture);
		}
	}

	void Cubemap::bind(unsigned int unit) const {
		glActiveTexture(GL_TEXTURE + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
	}

	unsigned int Cubemap::ID() const { return _cubemapTexture; }
}

