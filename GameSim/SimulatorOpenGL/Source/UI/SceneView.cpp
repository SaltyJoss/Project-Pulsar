#include "ch.h"

#include "SceneView.h"
#include <imgui.h>

namespace gui{
	void SceneView::render() {
		LightSpaceMatrix();
		ShadowPass();

		_frameBuffer->bind();

		WorldGridRender();
		MeshRender();
		
		_frameBuffer->unbind();

		ImGui::Begin("Simulation");

		_isHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		uint64_t textureID = _frameBuffer->getTexture();
		ImGui::Image((void*)textureID, viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();
	}

	void SceneView::resize(int32_t width, int32_t height) {
		float aspect = (float)width / (float)height;
		_camera->setAspect(aspect);

		_frameBuffer->deleteBuffers();
		float scale = 2.0f;
		_frameBuffer->createBuffers(width*2.0f, height*2.0f);

		LOG_INFO("Framebuffer resized", (int32_t)_size.x, (int32_t)_size.y);
	}

	std::shared_ptr<elements::Mesh> gui::SceneView::createCheckerPlane(float size) {

		auto plane = std::make_shared<elements::Mesh>();

		std::vector<glm::vec3> pos = {
			{-size, planeHeight, -size},
			{ size, planeHeight, -size},
			{ size, planeHeight,  size},
			{-size, planeHeight,  size}
		};

		glm::vec3 normal(0.0f, 1.0f, 0.0f);

		for (auto& p : pos) {
			elements::VertexHolder vh(p, normal);
			plane->addVertex(vh);
		}

		plane->addVertexIndex(0);
		plane->addVertexIndex(1);
		plane->addVertexIndex(2);
		plane->addVertexIndex(2);
		plane->addVertexIndex(3);
		plane->addVertexIndex(0);

		plane->init();
		return plane;
	}

	void SceneView::onMouseWheel(double delta) { 
		if (!_isHovered) return;

		if (_controlMode == ControlMode::Camera) _camera->onMouseWheel(delta);
		else if (_controlMode == ControlMode::Object && _mesh) _mesh->_position.z += (float)delta * 0.1f;
	}

	void SceneView::onMouseMove(double x, double y, elements::eInputButton button) { 
		glm::vec2 pos2d{ x, y };
		glm::vec2 delta = pos2d - _lastMousePos;
		_lastMousePos = pos2d;

		if (!_isHovered) {
			_camera->setCurrentPos2D(pos2d);
			_object->setLastMousePos(pos2d);
			return;
		}

		if (_controlMode == ControlMode::Camera) {
			_camera->onMouseMove(x, y, button);
		}
		else if (_controlMode == ControlMode::Object && _object) {
			_object->onMouseMove(x, y, button);
		}
	}

	void SceneView::loadMesh(const std::string& filepath) {
		if (!_mesh) _mesh = std::make_shared<elements::Mesh>();
		else _mesh->clear(); // implement clear() to delete VAO/VBO etc.
		_mesh->load(filepath);

		_mesh->_position = glm::vec3(0.0f);

		LOG_INFO("Mesh loaded and centered from %s", filepath.c_str());
	}

	/*
	 * --------------------------------------------
	 *				RENDERING METHODS
	 * --------------------------------------------
	 */

	void SceneView::WorldGridRender() {
		glDepthMask(GL_FALSE);
		glClearColor(_backgroundColour.r,
					 _backgroundColour.g,
					 _backgroundColour.b,
					 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		_worldGridShader->use();
		_worldGridShader->setMat4(_camera->getViewProjection(), "gVP");
		_worldGridShader->setVec3(_camera->getPosition(), "gCameraWorldPos");

		glBindVertexArray(_worldGridVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDepthMask(GL_TRUE);
	}

	void SceneView::MeshRender() {
		_shader->use();
		_shader->setMat4(_lightSpaceMatrix, "lightSpaceMatrix");

		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, _shadowMap);

		_shader->setInt1(7, "shadowMap");
		_camera->update(_shader.get());
		_light->update(_shader.get());

		// Render checker floor
		if (_checkerPlane) {
			glm::mat4 floorModel(1.0f);
			_shader->setMat4(floorModel, "model");

			// Set checkerboard uniforms
			_shader->setBool(true, "isFloor");
			_shader->setVec3(glm::vec3(1.0f), "colour1");
			_shader->setVec3(glm::vec3(0.0f), "colour2");
			_shader->setFlt1(1.0f, "checkSize");

			_checkerPlane->update(_shader.get());
			_checkerPlane->render();
		}

		if (_object && _object->getMesh()) {
			glm::mat4 model(1.0f);

			_shader->setMat4(glm::translate(glm::mat4(1.0f), _object->getMesh()->_position), "model");
			_shader->setBool(false, "isFloor");            // mark as non-floor
			_object->getMesh()->update(_shader.get());
			_object->getMesh()->render();
		}
	}

	void SceneView::LightSpaceMatrix() {
		glm::vec3 dir = (_light->_direction == glm::vec3(0))
			? glm::normalize(-_light->getPosition())
			: glm::normalize(_light->_direction);

		glm::mat4 lightView = glm::lookAt(
			-dir * 20.0f,
			glm::vec3(0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		glm::mat4 lightProj = glm::ortho(
			-10.0f, 10.0f,
			-10.0f, 10.0f,
			1.0f, 50.0f
		);

		_lightSpaceMatrix = lightProj * lightView;
	}

	void SceneView::InitShadowResource() {
		glGenFramebuffers(1, &_shadowFBO);

		glGenTextures(1, &_shadowMap);
		glBindTexture(GL_TEXTURE_2D, _shadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_W, SHADOW_H, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float border[] = { 1,1,1,1 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

		glBindFramebuffer(GL_FRAMEBUFFER, _shadowFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, _shadowMap, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void SceneView::ShadowPass() {
		glViewport(0, 0, SHADOW_W, SHADOW_H);
		glBindFramebuffer(GL_FRAMEBUFFER, _shadowFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		_shadowShader->use();
		_shadowShader->setMat4(_lightSpaceMatrix, "lightSpaceMatrix");

		// checker plane
		if (_checkerPlane) {
			glm::mat4 model(1.0f);
			_shadowShader->setMat4(model, "model");
			_checkerPlane->render();
		}

		// main mesh
		if (_object && _object->getMesh()) {
			glm::mat4 model =
				glm::translate(glm::mat4(1.0f), _object->getMesh()->_position);
			_shadowShader->setMat4(model, "model");
			_object->getMesh()->render();
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}