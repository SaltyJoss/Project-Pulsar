#pragma once
#include "EngineCore.h"

#include <vector>
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

using GLuint = unsigned int;

namespace elements {
    class ENGINE_API Face {
    private:
        std::vector<GLuint> _vertexIndices;

    public:
        void addVertexIndex(GLuint index) { _vertexIndices.push_back(index); }

    };
}