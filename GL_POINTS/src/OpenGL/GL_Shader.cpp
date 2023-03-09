#include "GL_Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "GL_gl.h"

namespace OpenGL
{
	Shader::Shader()
	{
		m_id = glCreateProgram();
	}

	Shader::Shader(const std::string& vsPath, const std::string& fsPath)
	{
		m_id = glCreateProgram();
		loadShader(vsPath, fsPath);
	}


	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}

	void Shader::loadShader(const std::string& vsPath, const std::string& fsPath)
	{
		uint32_t vs = createShader(vsPath, GL_VERTEX_SHADER);
		uint32_t fs = createShader(fsPath, GL_FRAGMENT_SHADER);

		glAttachShader(m_id, vs);
		glAttachShader(m_id, fs);
		glLinkProgram(m_id);

		GLint program_linked;
		glGetProgramiv(m_id, GL_LINK_STATUS, &program_linked);
		if (program_linked != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(m_id, 1024, &log_length, message);
			// Write the error to a log
		}

		glValidateProgram(m_id);
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	uint32_t Shader::createShader(const std::string& path, const int32_t& type)
	{
		const char* shaderSource = nullptr;
		std::stringstream shaderStrStream;
		std::ifstream shaderStream(path);
		if (shaderStream.is_open()) {
			shaderStrStream << shaderStream.rdbuf();
			shaderStream.close();
		}
		else {
			std::cout << "[ERROR][SHADER] Couldn't open shader (" + path + ")" << std::endl;
		}


		std::string sourceStr = shaderStrStream.str();
		shaderSource = sourceStr.c_str();
		uint32_t shader = glCreateShader(type);
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);


		int32_t shaderCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE) {
			int32_t logLength = 0;
			char msg[1024];
			glGetShaderInfoLog(shader, 1024, &logLength, msg);
			std::cout << "[ERROR][SHADER] Failed to compile with error: " << msg << std::endl;
		}
		return shader;
	}

	int32_t Shader::getUniformLocation(const std::string& name)
	{
		return glGetUniformLocation(m_id, name.c_str());
	}

	void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		int32_t location = getUniformLocation(name);
		if (location == -1) {
			std::cout << "[ERROR][SHADER] Couldn't find uniform: " << name << std::endl;
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void Shader::setUniform1i(const std::string& name, const int32_t& value)
	{
		int32_t location = getUniformLocation(name);
		if (location == -1) {
			std::cout << "[ERROR][SHADER] Couldn't find uniform: " << name << std::endl;
			return;
		}
		glUniform1i(location, value);
	}

	void Shader::setUniform1f(const std::string& name, const float& value)
	{
		int32_t location = getUniformLocation(name);
		if (location == -1) {
			std::cout << "[ERROR][SHADER] Couldn't find uniform: " << name << std::endl;
			return;
		}
		glUniform1f(location, value);
	}

	void Shader::bind() const
	{
		glUseProgram(m_id);
	}
}


