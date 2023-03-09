#include "GL_Context.h"

#include <iostream>

#include "GL_gl.h"

namespace OpenGL
{
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data)
	{
		std::cout << id << " " << type << " " << severity << " " << source << " " << msg << std::endl;
	}

	void Context::create()
	{
		if (glewInit() != GLEW_OK) {
			std::cout << "ERROR: Couldnt initialize GLEW" << std::endl;
		}
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugMessageCallback, NULL);
	}
}


