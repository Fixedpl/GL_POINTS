#include "GL_Renderer.h"

#include <iostream>
#include <glm/glm.hpp>



namespace OpenGL
{


	void Renderer::init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_PROGRAM_POINT_SIZE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::drawArrays(const VertexArray& buffer, const DrawUsage& draw_usage, const uint32_t& vertice_count)
	{
		glDrawArrays(static_cast<GLenum>(draw_usage), 0, vertice_count);
	}

	void Renderer::drawIndexed(const VertexArray& buffer, const DrawUsage& draw_usage, uint32_t size)
	{
		if (size == 0) {
			size = buffer.getIndexBuffer().getIndiceCount();
		}
		glDrawElements(static_cast<GLenum>(draw_usage), size, GL_UNSIGNED_INT, (void*)0);
	}
}


