/*#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_content(const char* filename);

class ShaderOld
{
	public:
		GLuint ID;
		ShaderOld(const char* vertexPath, const char* fragmentPath);	// Constructor that builds the shader program from 2 different shaders

		void Activate();	// Activates the Shader Program
		void Delete();		// Deletes the Shader Program

	private:
		void compileErrors(unsigned int shader, const char* type);	// Checks if DIFFERENT shaders have compiled properly
};

#endif*/