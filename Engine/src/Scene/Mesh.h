#pragma once

#include "ch.h"

#include "Render/RenderBase.h"
#include "VertexHolder.h"
#include "Element.h"

#include "Face.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace elements {
	class Mesh : public Element {
	public:
		Mesh() = default;
		
		virtual ~Mesh();

		bool load(const std::string& path);
		void addVertex(const VertexHolder& vertex) { _vertices.push_back(vertex); }
		void addVertexIndex(unsigned int vertexIndx) { _vertexIndices.push_back(vertexIndx); }
		
		void init();
		void createBuffers();
		void deleteBuffers();
		void render();
		void bind();
		void unbind();
		void clear();

		std::vector<unsigned int> getVertexIndices() { return _vertexIndices; }

		void update(shaders::Shader* shader) override {	// will use for specifying objects colour and texture
			shader->setVec3(_colour, "albedo");
			shader->setFlt1(_metallic, "metallic");
			shader->setFlt1(1.0f, "ao");
		}

		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _rotation = glm::vec3(0.0f);
		glm::vec3 _colour = { 0.0f, 0.0f, 1.0f };
		float _metallic = 0.1; // When rotating could be useful for seeing rotations with respect to a fixed light source.

	private:
		std::unique_ptr<render::VertexIndexBuffer> _rndrBffrMngr;
		
		std::vector<VertexHolder> _vertices;
		std::vector<unsigned int> _vertexIndices;
	};
}