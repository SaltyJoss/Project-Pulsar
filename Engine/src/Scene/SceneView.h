#pragma once

#include "Scene/Camera.h"
#include "Scene/Mesh.h"
#include "Scene/Light.h"
#include "Rendering/shaderUtil.h"
#include "Rendering/openglBufferManager.h"
#include "Scene/Input.h"
#include "Scene/Object.h"

extern Debug gLog; // Global Variable for debugging and logs

namespace gui {
    class SceneView{
    public:
        SceneView() :
            _camera(nullptr), _frameBuffer(nullptr), _shader(nullptr),
            _light(nullptr), _size(3840, 2160)
        {
            _frameBuffer = std::make_unique<render::OpenGLFrameBuffer>();
            _frameBuffer->createBuffers(3840, 2160);
            
            _shader = std::make_unique<shaders::Shader>();
            _shader->load("Engine/assets/shaders/vs_pbr.vert.glsl", "Engine/assets/shaders/fs_pbr.frag.glsl");

            _worldGridShader = std::make_unique<shaders::Shader>();
            _worldGridShader->load("Engine/assets/shaders/world_grid.vert.glsl", "Engine/assets/shaders/world_grid.frag.glsl");

            _shadowShader = std::make_unique<shaders::Shader>();
            _shadowShader->load("Engine/assets/shaders/shadow_depth.vert.glsl", "Engine/assets/shaders/shadow_depth.frag.glsl");
            
            _light = std::make_unique<elements::Light>();
            _camera = std::make_unique<elements::Camera>(glm::vec3(0, 15, 20), 45.0f, 1280.0f / 720.0f, 0.1f, 2000.0f);
            
            glGenVertexArrays(1, &_worldGridVAO);
            
            _mesh = std::make_shared<elements::Mesh>();
            _mesh->init();

            _object = std::make_shared<elements::Object>(_mesh);

            if (_checkerPlane) _checkerPlane->clear();
            _checkerPlane = createCheckerPlane(50.0f);

            InitShadowResource();
        }

        ~SceneView() {
            _shader->unload();
            if (_frameBuffer) _frameBuffer->deleteBuffers();
            if (_mesh) _mesh->clear();
            if (_checkerPlane) _checkerPlane->clear();
        }

        elements::Light* getLight() { return _light.get(); }
        void setBackgroundColour(const glm::vec3& c) { _backgroundColour = c; }
        glm::vec3 getBackgroundColour() const { return _backgroundColour; }

        void setBackgroundAlpha(float a) { _backgroundAlpha = a; }
        float getBackgroundAlpha() const { return _backgroundAlpha; }

        enum class ControlMode {
            Camera,
            Object
        };

        ControlMode _controlMode = ControlMode::Camera; // Default to Camera Control

        void render();
        void resize(int32_t width, int32_t height);
        void loadMesh(const std::string& filepath);
        void setMesh(std::shared_ptr<elements::Mesh> mesh) { _mesh = mesh; }
        void setControlMode(ControlMode mode) { _controlMode = mode; }
        ControlMode getControlMode() const { return _controlMode; }

        std::shared_ptr<elements::Mesh> getMesh() { return _mesh; }

        void onMouseMove(double x, double y, elements::eInputButton button);
        void onMouseWheel(double delta);
        void resetView() { _camera->reset(); }

        void MeshRender();
        void WorldGridRender();
        void LightSpaceMatrix();
        void InitShadowResource();
        void ShadowPass();

    private:       
        std::unique_ptr<render::OpenGLFrameBuffer> _frameBuffer;

        std::unique_ptr<shaders::Shader> _shader;
        std::unique_ptr<shaders::Shader> _worldGridShader;
        std::unique_ptr<shaders::Shader> _shadowShader;

        std::unique_ptr<elements::Light> _light;
        std::unique_ptr<elements::Camera> _camera;
        std::shared_ptr<elements::Object> _object;

        std::shared_ptr<elements::Mesh> _checkerPlane;
        std::shared_ptr<elements::Mesh> createCheckerPlane(float size = 50.0f);
        std::shared_ptr<elements::Mesh> _mesh;

        glm::vec2 _size;
        glm::vec2 _lastMousePos;
        glm::mat4 _lightSpaceMatrix;
        glm::vec3 _backgroundColour{ 1.0f, 1.0f, 1.0f };

        float _backgroundAlpha = 1.0f;
        float planeHeight = -2.5f;
        bool _isHovered = false;
        unsigned int _worldGridVAO = 0;
        unsigned int _shadowFBO;
        unsigned int _shadowMap;

        const unsigned int SHADOW_W = 2048;
        const unsigned int SHADOW_H = 2048;
    };
}