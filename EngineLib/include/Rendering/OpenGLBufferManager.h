#pragma once

#include "EngineCore.h"

#include "RenderBase.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace render {
	class OpenGLVertexIndexBuffer : public VertexIndexBuffer {
	public:
		OpenGLVertexIndexBuffer() : VertexIndexBuffer() {}

		void createBuffers(const std::vector<elements::VertexHolder>& vertices, const std::vector<unsigned int>& indices) override;
		void deleteBuffers() override;
		void bind() override;
		void unbind() override;
		void draw(int indxCount) override;
	};

	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		void createBuffers(int32_t width, int32_t height) override;
		void deleteBuffers() override;
		void bind() override;
		void unbind() override;
		uint32_t getTexture() override;
	};
}