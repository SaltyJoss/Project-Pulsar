#include "ch.h"
#include "OpenGLBufferManager.h"

namespace render {
	// --- OpenGLVertexIndexBuffer ---
	void render::OpenGLVertexIndexBuffer::createBuffers(const std::vector<elements::VertexHolder>& vertices, const std::vector<unsigned int>& indices) {
		LOG_INFO("Called createBuffers() with %zu vertices and %zu indices", vertices.size(), indices.size());

		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_EBO);
		glGenBuffers(1, &_VBO);

		if (!_VAO || !_EBO || !_VBO) { LOG_ERROR("Failed to generate VAO/VBO/EBO"); return; }

		glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(elements::VertexHolder), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(elements::VertexHolder), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(elements::VertexHolder), (void*)offsetof(elements::VertexHolder, _normal));

		glBindVertexArray(0);

		LOG_INFO("OpenGLVertexIndexBuffer buffers created successfully");
	}

	void render::OpenGLVertexIndexBuffer::deleteBuffers() {
		LOG_INFO("Deleting OpenGLVertexIndexBuffer buffers");

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_EBO);
		glDeleteBuffers(1, &_VBO);
		glDeleteVertexArrays(1, &_VAO);

		LOG_INFO("Buffers deleted");
	}

	void render::OpenGLVertexIndexBuffer::bind() { glBindVertexArray(_VAO); }

	void render::OpenGLVertexIndexBuffer::unbind() { glBindVertexArray(0); }

	void render::OpenGLVertexIndexBuffer::draw(int indxCount) {
		bind();
		glDrawElements(GL_TRIANGLES, indxCount, GL_UNSIGNED_INT, nullptr);
		unbind();
	}

	// --- OpenGLFrameBuffer ---
	void render::OpenGLFrameBuffer::createBuffers(int32_t width, int32_t height) {
		LOG_INFO("Creating framebuffer buffers with size %dx%d", width, height);
		_width = width;
		_height = height;

		if (_FBO) { 
			LOG_WARN("Framebuffer already exists. Deleting old buffers."); 
			deleteBuffers();
		}

		glGenFramebuffers(1, &_FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
		glCreateTextures(GL_TEXTURE_2D, 1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &_depthID);
		glBindTexture(GL_TEXTURE_2D, _depthID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthID, 0);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, buffers);

		unbind();

		LOG_INFO("Framebuffer buffers created successfully");
	}

	void render::OpenGLFrameBuffer::deleteBuffers() {
		if (_FBO) {
			LOG_INFO("Deleting framebuffer buffers");
			glDeleteFramebuffers(1, &_FBO);
			glDeleteTextures(1, &_texID);
			glDeleteTextures(1, &_depthID);
			_texID = 0;
			_depthID = 0;
			LOG_INFO("Framebuffer buffers deleted");
		}
		else { LOG_WARN("Attempted to delete framebuffer buffers but none exist"); }
	}

	void render::OpenGLFrameBuffer::bind() {
		if (!_FBO) { LOG_WARN_ONCE("Attempted to bind framebuffer but FBO is 0"); return; }
		glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
		glViewport(0, 0, _width, _height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void render::OpenGLFrameBuffer::unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	uint32_t render::OpenGLFrameBuffer::getTexture() { return _texID; }
}


