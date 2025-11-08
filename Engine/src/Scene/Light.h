#pragma once

#include "pch.h"

#include "Element.h"
#include "Rendering/ShaderUtil.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace elements {
    class Light : public Element
    {
    public:

        Light() {
            _direction = glm::vec3(-1.0f, -1.0f, -0.3f);
            _position = glm::vec3{ 1.5f, 3.5f, 3.0f };
            _colour = glm::vec3(1.0f, 1.0f, 1.0f);
            _strength = 250.0f;
            _size = 10.0f;
        }

        ~Light() {}

        glm::vec3 getPosition() const { return _position; }
        glm::vec3 getColour() const { return _colour; }

        void update(shaders::Shader* shader) override {
            shader->setVec3(_direction, "lightDirection");
            shader->setVec3(_position, "lightPosition");
            shader->setVec3(_colour * _strength, "lightColour");
            shader->setFlt1(_size, "lightSize");
        }

        glm::vec3 _direction;
        glm::vec3 _position;
        glm::vec3 _colour;
        float _strength;
        float _size;
    };
}