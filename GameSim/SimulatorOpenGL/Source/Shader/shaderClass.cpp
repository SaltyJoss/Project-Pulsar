/*#include "shaderClass.h"

// Function to read the contents of a file and return it as a string
std::string get_file_content(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (file) 
	{
		std::string contents;						// Create a string to hold the file contents
		file.seekg(0, std::ios::end);				// Move the file pointer to the end of the file
		contents.resize(file.tellg());				// Resize the string to fit the file contents
		file.seekg(0, std::ios::beg);				// Move the file pointer back to the beginning of the file
		file.read(&contents[0], contents.size());	// Read the file contents into the string
		file.close();								// Close the file
		return(contents);							// Return the file contents
	}
	throw(errno);
}

// Constructor that builds the shader program from 2 different shaders
ShaderOld::ShaderOld(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = get_file_content(vertexPath);		// Read vertex shader code from file
	std::string fragmentCode = get_file_content(fragmentPath);	// Read fragment shader code from file

	const char* vShaderCode = vertexCode.c_str();	// Convert vertex shader code to C-style string
	const char* fShaderCode = fragmentCode.c_str();	// Convert fragment shader code to C-style string

	GLuint vertexShader, fragmentShader; // Create shader object references

	vertexShader = glCreateShader(GL_VERTEX_SHADER);		// Create vertex shader object
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);	// Attach vertex shader source code
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");	// Checks if Shader compiled succesfully

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// Create fragment shader object
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);	// Attach fragment shader source code
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");	// Checks if Shader compiled succesfully

	ID = glCreateProgram();	// Create shader program

	glAttachShader(ID, vertexShader);		// Attach vertex shader	
	glAttachShader(ID, fragmentShader);	// Attach fragment shader
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");	// Checks if Shader linked succesfully

	glDeleteShader(vertexShader);		// Delete vertex shader
	glDeleteShader(fragmentShader);	// Delete fragment shader
}

// Activate the shader program
void ShaderOld::Activate()
{
	glUseProgram(ID);
}

// Delete the shader program
void ShaderOld::Delete()
{
	glDeleteProgram(ID);
}

// Error Handling
void ShaderOld::compileErrors(unsigned int shader, const char* type) 
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "[SHADER_COMPILATION_ERROR]: " << type << " ->\n\t" 
				<< infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "[SHADER_LINKING_ERROR]: " << type << " ->\n\t" 
				<< infoLog << std::endl;
		}
	}
}*/
