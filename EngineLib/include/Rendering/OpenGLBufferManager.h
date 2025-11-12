#pragma once
#include "EngineCore.h"

#include "RenderBase.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace render {
	class ENGINE_API OpenGLVertexIndexBuffer : public VertexIndexBuffer {
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