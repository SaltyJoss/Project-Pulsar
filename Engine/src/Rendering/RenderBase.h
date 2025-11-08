#pragma once

#include "Window/Window.h"
#include "Elements/VertexHolder.h"

namespace render {
	class VertexIndexBuffer {
	public:
		// Replaces and Centralises old VAO, VBO, EBO classes -> See OpenGLBufferManager
		VertexIndexBuffer() : _VAO{ 0 }, _VBO{ 0 }, _EBO{ 0 } {}

		virtual void createBuffers(const std::vector<elements::VertexHolder>& verticies, const std::vector<unsigned int>& indices) = 0;
		virtual void deleteBuffers() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void draw(int indxCount) = 0;

	protected:
		GLuint _VAO;
		GLuint _VBO;
		GLuint _EBO;
	};

	class FrameBuffer {
	public:
		// This was NOT working in previous version, so revised code with docs and research -> See OpenGLBufferManager
		FrameBuffer() : _FBO{ 0 }, _depthID{ 0 } {}

		virtual void createBuffers(int32_t width, int32_t height) = 0;
		virtual void deleteBuffers() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual uint32_t getTexture() = 0;

	protected:
		uint32_t _FBO = 0;
		uint32_t _texID = 0;
		uint32_t _depthID = 0;

		int32_t _width = 0;
		int32_t _height = 0;
	};

	class RenderContext {
	public:
		// Centeralised way to gain context on the renders' process -> see OpenGLContext
		RenderContext() : _window(nullptr) {}

		virtual bool init(window::IWindow* win) {
			_window = win;
			return true;
		}

		virtual void preRender() = 0;
		virtual void postRender() = 0;
		virtual void end() = 0;

	protected:
		window::IWindow* _window;
	};
}