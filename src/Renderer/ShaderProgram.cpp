#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertexShader, std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile-time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
}
