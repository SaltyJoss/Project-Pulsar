#include "pch.h"
#include "Scene/AxisOrientator.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <string>

#include <imgui.h> // needed if you keep any ImGui usage

namespace gui {

    GLuint AxisOrientator::g_VAO = 0;
    GLuint AxisOrientator::g_VBO = 0;
    GLuint AxisOrientator::g_VAOCones = 0;
    GLuint AxisOrientator::g_VBOCones = 0;
    GLuint AxisOrientator::g_Shader = 0;

    bool AxisOrientator::g_Initialised = false;
    int AxisOrientator::g_ConeVertexCount = 0;

    void AxisOrientator::init() {
        // Interleaved (pos, color)
        float vertices[] = {
            // X axis (red)
            0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
            // Y axis (green)
            0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            // Z axis (blue)
            0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f
        };

        glGenVertexArrays(1, &g_VAO);
        glGenBuffers(1, &g_VBO);

        glBindVertexArray(g_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Cones for tip (looked this up online, logged for future reference)
        const int segments = 16;
        const float radius = 0.08f;
        const float tipOffset = 0.25f;   // how far past the axis end the tip goes

        std::vector<float> coneVertices;
        coneVertices.reserve(3 * segments * 3 * 2 * 6); // 3 axes * segments * (base+side) * 3 verts * 6 floats

        auto addCone = [&](const glm::vec3& baseCenter,
            const glm::vec3& tip,
            const glm::vec3& u,
            const glm::vec3& v,
            const glm::vec3& colour)
            {
                // u and v span the circle plane (orthonormal-ish)
                for (int i = 0; i < segments; ++i) {
                    float theta0 = (float(i) / segments) * 2.0f * glm::pi<float>();
                    float theta1 = (float(i + 1) / segments) * 2.0f * glm::pi<float>();

                    glm::vec3 p0 = baseCenter + radius * (std::cos(theta0) * u + std::sin(theta0) * v);
                    glm::vec3 p1 = baseCenter + radius * (std::cos(theta1) * u + std::sin(theta1) * v);

                    // (Optional) base cap triangle: baseCenter, p1, p0
                    // You can omit this if you don't care about the base disk.
                    auto pushVertex = [&](const glm::vec3& p) {
                        coneVertices.push_back(p.x);
                        coneVertices.push_back(p.y);
                        coneVertices.push_back(p.z);
                        coneVertices.push_back(colour.r);
                        coneVertices.push_back(colour.g);
                        coneVertices.push_back(colour.b);
                        };

                    // Base cap (not super visible, but keeps it watertight)
                    pushVertex(baseCenter);
                    pushVertex(p1);
                    pushVertex(p0);

                    // Side triangle: tip, p0, p1
                    pushVertex(tip);
                    pushVertex(p0);
                    pushVertex(p1);
                }
            };

        // X-axis cone: base at (1,0,0), tip along +X
        {
            glm::vec3 baseCenter(1.0f, 0.0f, 0.0f);
            glm::vec3 tip(1.0f + tipOffset, 0.0f, 0.0f);
            glm::vec3 u(0.0f, 1.0f, 0.0f); // circle basis
            glm::vec3 v(0.0f, 0.0f, 1.0f);
            glm::vec3 colour(1.0f, 0.0f, 0.0f);
            addCone(baseCenter, tip, u, v, colour);
        }

        // Y-axis cone: base at (0,1,0), tip along +Y
        {
            glm::vec3 baseCenter(0.0f, 1.0f, 0.0f);
            glm::vec3 tip(0.0f, 1.0f + tipOffset, 0.0f);
            glm::vec3 u(1.0f, 0.0f, 0.0f);
            glm::vec3 v(0.0f, 0.0f, 1.0f);
            glm::vec3 colour(0.0f, 1.0f, 0.0f);
            addCone(baseCenter, tip, u, v, colour);
        }

        // Z-axis cone: base at (0,0,1), tip along +Z
        {
            glm::vec3 baseCenter(0.0f, 0.0f, 1.0f);
            glm::vec3 tip(0.0f, 0.0f, 1.0f + tipOffset);
            glm::vec3 u(1.0f, 0.0f, 0.0f);
            glm::vec3 v(0.0f, 1.0f, 0.0f);
            glm::vec3 colour(0.0f, 0.0f, 1.0f);
            addCone(baseCenter, tip, u, v, colour);
        }

        g_ConeVertexCount = static_cast<int>(coneVertices.size() / 6); // 6 floats per vertex

        glGenVertexArrays(1, &g_VAOCones);
        glGenBuffers(1, &g_VBOCones);

        glBindVertexArray(g_VAOCones);
        glBindBuffer(GL_ARRAY_BUFFER, g_VBOCones);
        glBufferData(GL_ARRAY_BUFFER,
            coneVertices.size() * sizeof(float),
            coneVertices.data(),
            GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        const char* vertexShaderSrc = R"(
            #version 460 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec3 aColour;

            uniform mat4 uView;
            uniform mat4 uProjection;

            out vec3 ourColour;

            void main() {
                ourColour = aColour;
                gl_Position = uProjection * uView * vec4(aPos, 1.0);
            }
        )";

        // Shaders 
        const char* fragmentShaderSrc = R"(
            #version 460 core
            in vec3 ourColour;
            out vec4 FragColour;

            void main() {
                FragColour = vec4(ourColour, 1.0);
            }
        )";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexShaderSrc, nullptr);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShaderSrc, nullptr);
        glCompileShader(fs);

        g_Shader = glCreateProgram();
        glAttachShader(g_Shader, vs);
        glAttachShader(g_Shader, fs);
        glLinkProgram(g_Shader);

        glDeleteShader(vs);
        glDeleteShader(fs);

        g_Initialised = true;
    }

    void AxisOrientator::render(const glm::mat4& viewMatrix) {
        if (!g_Initialised) init();

        // 1) Use current viewport (whatever FBO / window is bound)
        GLint prevViewport[4];
        glGetIntegerv(GL_VIEWPORT, prevViewport);
        int fbWidth = prevViewport[2];
        int fbHeight = prevViewport[3];

        const int orientatorSize = 150; // pixels
        const int margin = 10;

        int x = margin;
        int y = margin;

        GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
        GLboolean blendEnabled = glIsEnabled(GL_BLEND);

        // 2) Set small viewport for the gizmo
        glViewport(x, y, orientatorSize, orientatorSize);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);

        // Small camera looking at origin
        glm::mat4 viewOrientator = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f), // eye
            glm::vec3(0.0f, 0.0f, 0.0f), // center
            glm::vec3(0.0f, 1.0f, 0.0f)  // up
        );

        glm::mat4 projOrientator = glm::perspective(
            glm::radians(45.0f),
            1.0f,       // square viewport
            0.1f,
            100.0f
        );

        // Extract camera orientation from main view
        glm::mat4 invView = glm::inverse(viewMatrix);
        glm::mat4 rot = glm::mat4(glm::mat3(invView)); // drop translation

        // World -> rot -> viewOrientator
        glm::mat4 gizmoView = viewOrientator * rot;

        // 4) Draw
        glUseProgram(g_Shader);

        GLint viewLoc = glGetUniformLocation(g_Shader, "uView");
        GLint projLoc = glGetUniformLocation(g_Shader, "uProjection");

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &gizmoView[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projOrientator[0][0]);

        glBindVertexArray(g_VAO);
        glLineWidth(2.5f);
        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);

        glBindVertexArray(g_VAOCones);
        glDrawArrays(GL_TRIANGLES, 0, g_ConeVertexCount);
        glBindVertexArray(0);

        glUseProgram(0);

        // 5) Restore GL state
        if (depthTestEnabled) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        if (blendEnabled)     glEnable(GL_BLEND);      else glDisable(GL_BLEND);

        glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
    }
}