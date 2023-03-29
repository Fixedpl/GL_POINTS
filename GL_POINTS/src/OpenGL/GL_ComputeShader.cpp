#include "GL_ComputeShader.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "GL_gl.h"


OpenGL::ComputeShader::ComputeShader()
{
	m_id = glCreateProgram();
}

OpenGL::ComputeShader::ComputeShader(const std::string& path)
{
	m_id = glCreateProgram();
}

OpenGL::ComputeShader::~ComputeShader()
{
	glDeleteProgram(m_id);
}

void OpenGL::ComputeShader::bind() const
{
	glUseProgram(m_id);
}

void OpenGL::ComputeShader::loadShader(const std::string& path)
{
	uint32_t cs = createShader(path, GL_COMPUTE_SHADER);

	glAttachShader(m_id, cs);
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
	glDeleteShader(cs);
}

uint32_t OpenGL::ComputeShader::createShader(const std::string& path, const int32_t& type)
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
