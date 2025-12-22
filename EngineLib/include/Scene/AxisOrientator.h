#pragma once

//=============================================
//            File: simManager.h
//=============================================
// Class representing a 3D scene view with camera, lighting, and object management.
// 
// Summary:
// ============================================
// 
// public:
// --------------------------------------------
// void render()
//		-> Renders the axis orientator, given the current view matrix.
// --------------------------------------------
// 
// private:
// --------------------------------------------
// void init()
//		-> Initializes the axis orientator resources, including VAOs, VBOs, and shaders - deals with setting up the geometry for the axes and cones
//		-> Does a lot of OpenGL buffer setup and shader compilation, so it's separated out for clarity.
//		-> May seperate this further if it gets too large, no plans to extend it at the moment.
// static GLuint g_VAO
//		-> OpenGL Vertex Array Object ID for the axis lines.
// static GLuint g_VBO
// 		-> OpenGL Vertex Buffer Object ID for the axis lines.
// static GLuint g_VAOCones
// 		-> OpenGL Vertex Array Object ID for the axis cones.
// static GLuint g_VBOCones
// 		-> OpenGL Vertex Buffer Object ID for the axis cones.
// static GLuint g_Shader
// 		-> OpenGL Shader Program ID for rendering the axis orientator.
// static bool g_Initialised
// 		-> Flag indicating whether the axis orientator has been initialized.
// static int g_ConeVertexCount
// 		-> Number of vertices used to render the cones at the ends of the axes.
// --------------------------------------------
//
// ============================================
//              GitHub: SaltyJoss
// ============================================

#include "EngineCore.h"
#include <glad/glad.h>

namespace gui {
	class ENGINE_API AxisOrientator
	{
	public:
		void render(const glm::mat4& viewMatrix);

	private:
		void init();

		static GLuint g_VAO;		// lines
		static GLuint g_VBO;		// lines
		static GLuint g_VAOCones;   // cones
		static GLuint g_VBOCones;   // cones
		static GLuint g_Shader;

		static bool g_Initialised;
		static int g_ConeVertexCount;
	};
}