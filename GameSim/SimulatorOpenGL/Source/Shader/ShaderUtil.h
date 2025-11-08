#pragma once

#include "ch.h"

namespace shaders {
	class Shader {
	private:
		unsigned int _programID;
		unsigned int getCompiledShader(unsigned int shaderType, const std::string& shaderSource);

	public:
		Shader() = default;

		bool load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
		void use();
		void unload();

		unsigned int getProgramID() { return _programID; }

		void setMat4(const glm::mat4& mat4, const std::string& name);
		void setInt1(int v, const std::string& name);
		void setFlt1(float v, const std::string& name);
		void setFlt3(float a, float b, float c, const std::string& name);
		void setVec3(const glm::vec3& vec3, const std::string& name);
		void setVec4(const glm::vec4& vec4, const std::string& name);
		void setBool(bool value, const std::string& name);
	};
}