#pragma once
#include "EngineCore.h"

#include "Scene/Input.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>
#include "FpsCounter.h"
#include "Platform/Logger.h"

extern ENGINE_API Debug gLog;

namespace render {
    class OpenGLFrameBuffer;
	class IBL;
    class Cubemap;
    class SkyboxRenderer;
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
    class AxisOrientator;
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

        float getPlaneHeight() const { return planeHeight; }

        enum class ControlMode {
            Camera,
            Object
        };

        elements::Camera* getCamera();
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
        void updatePhysics(float dt);

        void handleContinuousMovement(GLFWwindow* window, float dt);
		void processMovementKey(int key, float delta);

        void resetMouseDelta();
		void handleMouseLook(GLFWwindow* window, double xpos, double ypos);

        void loadNewHDR(const std::string& path);

        void resetView();

    private:       
        void MeshRender();
        void WorldGridRender();
        glm::mat4 LightSpaceMatrix(float near, float far);
        void InitShadowResource();
        void InitIBL();
        void ShadowPass();
        void SkyboxRender();

        std::unique_ptr<render::OpenGLFrameBuffer> _frameBuffer;

        std::unique_ptr<render::Cubemap> _cubemap;
        std::unique_ptr<render::SkyboxRenderer> _skybox;
        std::unique_ptr<shaders::Shader> _skyboxShader;

        std::unique_ptr<shaders::Shader> _shader;
        std::unique_ptr<shaders::Shader> _worldGridShader;
        std::unique_ptr<shaders::Shader> _shadowShader;
        std::unique_ptr<render::IBL> _ibl;

        std::unique_ptr<elements::Light> _light;
        std::unique_ptr<elements::Camera> _camera;
        std::shared_ptr<elements::Object> _object;

        std::shared_ptr<elements::Mesh> _checkerPlane;
        std::shared_ptr<elements::Mesh> createCheckerPlane(float size = 50.0f);
        std::shared_ptr<elements::Mesh> _mesh;
        std::unique_ptr<AxisOrientator> _axisOrientator;

        gui::FpsCounter _fpsCounter;

        glm::vec2 _size;
        glm::vec2 _lastMousePos = { 0.f, 0.f };
        glm::mat4 _lightSpaceMatrix;
        glm::vec3 _backgroundColour{ 1.0f, 1.0f, 1.0f };
        glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);

        std::string folder = "s3";

        float _backgroundAlpha = 1.0f;
        float planeY = planeHeight;

        bool _isHovered = false;
        bool skyboxEnabled = true;
        bool _firstMouse = true;
        bool _firstUpdate = true;

        unsigned int _worldGridVAO = 0;

        static constexpr float planeHeight = -2.5f;
        
/*
 * --------------------------------------------------------------------------
 *                          Shadow Mapping Settings
 * --------------------------------------------------------------------------
 */        

        unsigned int _shadowFBO = 0;
        unsigned int _shadowMap = 0;

		uint32_t _envCubemap = 0;
		uint32_t _irradianceMap = 0;
		uint32_t _prefilterMap = 0;
		uint32_t _brdfLUT = 0;

		static constexpr int NUM_CASCADES = 4;

        GLuint _cascadeFBO[NUM_CASCADES];
        GLuint _cascadeDepth[NUM_CASCADES];

		glm::mat4 _lightSpaceMatrixCascade[NUM_CASCADES];
        float _cascadeSplits[NUM_CASCADES] = {0.1f, 0.3f};

/*
 * --------------------------------------------------------------------------
 *                          Grapical Settings
 * --------------------------------------------------------------------------
 */
        // Shadow map dimensions
		const unsigned int SHADOW_W = 8192; 
		const unsigned int SHADOW_H = 8192; 
    };
}