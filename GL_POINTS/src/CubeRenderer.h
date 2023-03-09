#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"




class CubeRenderer
{
public:

	void addCubeAt(const glm::vec3& pos);

	void init();

	void render();

private:

	const uint32_t m_size_of_cube = 4 * 3 * 3 * 3 * 2 * 6;

	std::vector<glm::vec3> m_cube_positions;

	OpenGL::VertexArray* m_test_cube_vao;
	OpenGL::VertexBuffer* m_test_cube_vbo;
	OpenGL::BufferLayout* m_test_cube_vbo_layout;

};

