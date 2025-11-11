#include "pch.h"

#include <imgui.h>

#include "ControlPanel.h"

void gui::ControlPanel::render(gui::SceneView* sceneView) {
    _sceneView = sceneView; // store pointer for convenience
    _mesh = sceneView->getMesh();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.129f, 0.129f, 0.129f, 0.8f));
    ImGui::Begin("Control Panel", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Open")) { _fileDialog.Open(); LOG_INFO("File dialog opened"); }
    ImGui::SameLine(0, 5.0f);
    ImGui::Text(_currentFile.c_str());

    if (ImGui::CollapsingHeader("Camera Settings")) { renderCameraProperties(); }
    if (ImGui::CollapsingHeader("Simulation Settings")) { renderSimulationProperties(); renderObjectProperties(); renderLinkProperties(); renderStats(); }
    if (ImGui::CollapsingHeader("Display Settings")) { renderDisplaySettings(); }

    ImGui::End();
    ImGui::PopStyleColor();

    _fileDialog.Display();
    if (_fileDialog.HasSelected()) {
        auto file_path = _fileDialog.GetSelected().string();
        _currentFile = file_path.substr(file_path.find_last_of("/\\") + 1);
        _meshLoadCallback(file_path);
        LOG_INFO("Mesh loaded from file: %s", _currentFile.c_str());
        
        _fileDialog.ClearSelected();
    }
}

void gui::ControlPanel::renderSimulationProperties() {
    ImGui::SeparatorText("Simulation Controls");
    static bool physicsEnabled = true;
    static bool gravityEnabled = true;
    ImGui::Checkbox("Enable Physcics", &physicsEnabled);
    ImGui::Checkbox("Enable Gravity", &gravityEnabled);
}

void gui::ControlPanel::renderObjectProperties() {
    ImGui::SeparatorText("Object Controls");
    static char velocityBuf[64] = "";
    static char torqueBuf[64] = "";
    ImGui::InputText("Velocity", velocityBuf, IM_ARRAYSIZE(velocityBuf));
    ImGui::InputText("Torque", torqueBuf, IM_ARRAYSIZE(torqueBuf));
}

void gui::ControlPanel::renderLinkProperties() {
    ImGui::SeparatorText("Link Controls");
    static char linkLengthBuf[64] = "";
    static char dampingBuf[64] = "";
    ImGui::InputText("Link Length", linkLengthBuf, IM_ARRAYSIZE(linkLengthBuf));
    ImGui::InputText("Damping", dampingBuf, IM_ARRAYSIZE(dampingBuf));
}

void gui::ControlPanel::renderStats() {
    ImGui::SeparatorText("Simulation Statistics");
    static float data[100];
    for (int i = 0; i < 100; i++) data[i] = sinf(i * 0.1f);
    ImGui::PlotLines("Velocity", data, 100);
}

void gui::ControlPanel::renderCameraProperties() {
    ImGui::SeparatorText("Background");

    glm::vec3 col = _sceneView->getBackgroundColour();
    if (ImGui::ColorEdit3("Canvas Colour", &col.x)) {
        _sceneView->setBackgroundColour(col);
    }
    float a = _sceneView->getBackgroundAlpha();
    if (ImGui::SliderFloat("Alpha", &a, 0.0f, 1.0f)) {
        _sceneView->setBackgroundAlpha(a);
    }

    ImGui::Text("Control Mode:");
    if (ImGui::RadioButton("Camera", *_controlMode == SceneView::ControlMode::Camera))
        *_controlMode = SceneView::ControlMode::Camera;
    ImGui::SameLine();
    if (ImGui::RadioButton("Object", *_controlMode == SceneView::ControlMode::Object))
        *_controlMode = SceneView::ControlMode::Object;

    ImGui::SeparatorText("Light Controls");
    elements::Light* light = _sceneView->getLight();

    ImGui::DragFloat3("Light Position", &light->_position.x, 0.1f);
    ImGui::DragFloat("Strength", &light->_strength, 0.1f, 0.0f, 500.0f);
    ImGui::DragFloat3("Light Direction", &light->_direction.x, 0.01f);
    if (glm::length(light->_direction) > 0.001f)
        light->_direction = glm::normalize(light->_direction);

    ImGui::SeparatorText("Object Appearance");
    if (!_mesh) {
        ImGui::Text("No mesh loaded!");
        LOG_WARN_ONCE("No mesh loaded while rendering Object Appearance");
    }
    else {
        ImGui::ColorPicker3("Color", glm::value_ptr(_mesh->_colour), ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB);
        ImGui::SliderFloat("Metallic", &_mesh->_metallic, 0.0f, 1.0f);
    }
}

void gui::ControlPanel::renderDisplaySettings() {
    ImGui::SeparatorText("Display Settings");
}
