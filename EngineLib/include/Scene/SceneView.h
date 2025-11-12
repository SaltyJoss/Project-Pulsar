#pragma once
#include "EngineCore.h"

#include "Scene/Input.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace render {
    class OpenGLFrameBuffer;
    class Cubemap;
    class Skybox;
}
namespace shaders {
    class Shader;
}
namespace elements {
    class Light;
    class Camera;
    class Input;
    class Mesh;
    class Object;
}

extern Debug gLog;

namespace gui {
    class ENGINE_API SceneView{
    public:
        SceneView();
        ~SceneView();

        elements::Light* getLight() { return _light.get(); }

        bool isSkyboxEnabled() const { return skyboxEnabled; }
        void setSkyboxEnabled(bool b) { skyboxEnabled = b; }

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
        void resetView();

    private:       
        void MeshRender();
        void WorldGridRender();
        void LightSpaceMatrix();
        void InitShadowResource();
        void ShadowPass();
        void SkyboxRender();

        std::unique_ptr<render::OpenGLFrameBuffer> _frameBuffer;

        std::unique_ptr<render::Cubemap> _cubemap;
        std::unique_ptr<render::Skybox> _skybox;
        std::unique_ptr<shaders::Shader> _skyboxShader;

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

        std::string folder = "s3";

        float _backgroundAlpha = 1.0f;
        float planeHeight = -2.5f;

        bool _isHovered = false;
        bool skyboxEnabled = true;

        unsigned int _worldGridVAO = 0;
        unsigned int _shadowFBO = 0;
        unsigned int _shadowMap = 0;

        const unsigned int SHADOW_W = 2048;
        const unsigned int SHADOW_H = 2048;
    };
}