#pragma once

#include "EngineCore.h"

namespace elements {
    class Face {
    private:
        std::vector<GLuint> _vertexIndices;

    public:
        void addVertexIndex(GLuint index) { _vertexIndices.push_back(index); }

    };
}