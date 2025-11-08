/*#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include "ch.h"
#include "Shader/shaderClass.h"

class SimulationManager
{
private:
    class Buffers {
    public:
        static const GLfloat vertices[];
        static const GLuint indices[];
    };

    std::unique_ptr<Shader> shaderProgram;

    VAO _VAO;
    VBO _VBO;
    EBO _EBO;

	GLuint uniID;

    GLuint fbo = 0;
    GLuint fboTexture = 0;
    GLuint rbo = 0;
    int width = 1280, height = 720;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

public:
    bool Init();            // create shaders, buffers, etc.
    void Update(float dt);  // update logic or physics
    void Render(int width, int height);          // issue OpenGL draw calls
    GLuint GetTextureID() const { return fboTexture; }
    void Resize(int w, int h); // optional
    void Terminate();       // release GPU resources
};

#endif*/
