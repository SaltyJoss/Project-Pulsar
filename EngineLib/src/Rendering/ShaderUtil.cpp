
#include "pch.h"

#include "Rendering/ShaderUtil.h"

namespace shaders {
	unsigned int Shader::getCompiledShader(unsigned int shaderType, const std::string& shaderSource) {
		unsigned int shaderID = glCreateShader(shaderType);
		const char* cSource = shaderSource.c_str();

		glShaderSource(shaderID, 1, &cSource, nullptr);
		glCompileShader(shaderID);

		GLint result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

			GLchar* infoLog = new GLchar[length + 1];
			glGetShaderInfoLog(shaderID, length, &length, infoLog);

			LOG_ERROR("Shader compilation failed: %s", infoLog);
			delete[] infoLog;
		} else { LOG_INFO("Shader compiled successfully"); }

		return shaderID;
	}

	bool Shader::load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
		std::ifstream isVS(vertexShaderFile);
		std::ifstream isFS(fragmentShaderFile);

		if (!isVS.is_open() || !isFS.is_open()) {
			LOG_ERROR("Failed to open shader files: VS=%s FS=%s", vertexShaderFile.c_str(), fragmentShaderFile.c_str());
			return false;
		}

		const std::string fVS((std::istreambuf_iterator<char>(isVS)), std::istreambuf_iterator<char>());
		const std::string fFS((std::istreambuf_iterator<char>(isFS)), std::istreambuf_iterator<char>());

		_programID = glCreateProgram();

		unsigned int vs = getCompiledShader(GL_VERTEX_SHADER, fVS);
		unsigned int fs = getCompiledShader(GL_FRAGMENT_SHADER, fFS);

		glAttachShader(_programID, vs);
		glAttachShader(_programID, fs);

		glLinkProgram(_programID);

		GLint linkStatus;
		glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			int length;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &length);
			GLchar* infoLog = new GLchar[length + 1];
			glGetProgramInfoLog(_programID, length, &length, infoLog);
			LOG_ERROR("Shader program linking failed: %s", infoLog);
			delete[] infoLog;
		}
		else { LOG_INFO("Shader program linked successfully"); }

		glValidateProgram(_programID);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return true;
	}

	void Shader::use() { glUseProgram(_programID); LOG_INFO_ONCE("Shader program bound"); }
	void Shader::unload() { glDeleteProgram(_programID); LOG_INFO_ONCE("Shader program deleted"); }

	void Shader::setMat4(const glm::mat4& mat4, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(mat4));
	}

	void Shader::setInt1(int v, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glUniform1i(matLoc, v);
	}

	void Shader::setFlt1(float v, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glUniform1f(matLoc, v);
	}

	void Shader::setFlt3(float a, float b, float c, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glUniform3f(matLoc, a, b, c);
	}

	void Shader::setVec3(const glm::vec3& vec3, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glProgramUniform3fv(getProgramID(), matLoc, 1, glm::value_ptr(vec3));
	}

	void Shader::setVec4(const glm::vec4& vec4, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glProgramUniform4fv(getProgramID(), matLoc, 1, glm::value_ptr(vec4));
	}

	void Shader::setBool(bool value, const std::string& name) {
		GLint matLoc = glGetUniformLocation(getProgramID(), name.c_str());
		glUniform1i(matLoc, value ? 1 : 0);  // use glUniform1i for bool
	}
}