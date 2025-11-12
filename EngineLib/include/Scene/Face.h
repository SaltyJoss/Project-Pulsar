#pragma once

#include "EngineCore.h"
#include <vector>

using GLuint = unsigned int;

namespace elements {
    class Face {
    private:
        std::vector<GLuint> _vertexIndices;

    public:
        void addVertexIndex(GLuint index) { _vertexIndices.push_back(index); }

    };
}