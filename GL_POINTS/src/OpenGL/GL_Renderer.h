#pragma once
#include <unordered_map>

#include "GL_VertexBuffer.h"
#include "GL_Shader.h"



namespace OpenGL
{
	class Renderer
	{
	public:

		static void init();

		static void setClearColor(const glm::vec4& color);
		static void clear();

		static void drawArrays(const VertexArray& buffer, const DrawUsage& draw_usage, const uint32_t& vertice_count);
		static void drawIndexed(const VertexArray& buffer, const DrawUsage& draw_usage, uint32_t size = 0);

	};
}
