#include "CubeRenderer.h"

#include "OpenGL/GL_Renderer.h"

void CubeRenderer::addCubeAt(const glm::vec3& pos)
{
	m_cube_positions.push_back(pos);
}

void CubeRenderer::init()
{
	m_test_cube_vao = new OpenGL::VertexArray();
	m_test_cube_vao->bind();

	m_test_cube_vbo = new OpenGL::VertexBuffer(m_size_of_cube * m_cube_positions.size(), DrawType::STATIC);
	m_test_cube_vbo_layout = new OpenGL::BufferLayout();
	m_test_cube_vbo_layout->addAttribute<float>(3);
	m_test_cube_vbo_layout->addAttribute<float>(3);

	m_test_cube_vao->addVertexBuffer(m_test_cube_vbo);
	m_test_cube_vao->setBufferLayout(*m_test_cube_vbo_layout);

	
	glm::vec3 red =		glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 green =	glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 blue =	glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 yellow =	glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 pink =	glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 orange =	glm::vec3(1.0f, 0.5f, 0.0f);

	glm::vec3 front_color = yellow;
	glm::vec3 right_color = blue;
	glm::vec3 left_color =	green;
	glm::vec3 back_color = orange;
	glm::vec3 bottom_color = red;
	glm::vec3 top_color = pink;


	for (int i = 0; i < m_cube_positions.size(); ++i) {
		glm::vec3 position = m_cube_positions[i];

		glm::vec3 v0 = position + glm::vec3(-1.0f, -1.0f, -1.0f);
		glm::vec3 v1 = position + glm::vec3(1.0f, -1.0f, -1.0f);
		glm::vec3 v2 = position + glm::vec3(1.0f, 1.0f, -1.0f);
		glm::vec3 v3 = position + glm::vec3(-1.0f, 1.0f, -1.0f);
		glm::vec3 v4 = position + glm::vec3(-1.0f, -1.0f, 1.0f);
		glm::vec3 v5 = position + glm::vec3(1.0f, -1.0f, 1.0f);
		glm::vec3 v6 = position + glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 v7 = position + glm::vec3(-1.0f, 1.0f, 1.0f);

		float test_cube_data[] = {

			//////
			// front

			 v0.x,  v0.y,  v0.z,   front_color.x, front_color.y, front_color.z, // v0
			 v1.x,  v1.y,  v1.z,   front_color.x, front_color.y, front_color.z, // v1
			 v2.x,  v2.y,  v2.z,   front_color.x, front_color.y, front_color.z, // v2

			 v0.x,  v0.y,  v0.z,   front_color.x, front_color.y, front_color.z, // v0
			 v2.x,  v2.y,  v2.z,   front_color.x, front_color.y, front_color.z, // v2
			 v3.x,  v3.y,  v3.z,   front_color.x, front_color.y, front_color.z, // v3

			 //////
			 // right

			  v1.x,  v1.y,  v1.z,   right_color.x, right_color.y, right_color.z, // v1
			  v5.x,  v5.y,  v5.z,   right_color.x, right_color.y, right_color.z, // v5
			  v6.x,  v6.y,  v6.z,   right_color.x, right_color.y, right_color.z, // v6

			  v1.x,  v1.y,  v1.z,   right_color.x, right_color.y, right_color.z, // v1
			  v2.x,  v2.y,  v2.z,   right_color.x, right_color.y, right_color.z, // v2
			  v6.x,  v6.y,  v6.z,   right_color.x, right_color.y, right_color.z, // v6

			  //////
			   // left

			   v0.x,  v0.y,  v0.z,   left_color.x, left_color.y, left_color.z, // v0
			   v4.x,  v4.y,  v4.z,   left_color.x, left_color.y, left_color.z, // v4
			   v7.x,  v7.y,  v7.z,   left_color.x, left_color.y, left_color.z, // v7

			   v0.x,  v0.y,  v0.z,   left_color.x, left_color.y, left_color.z, // v0
			   v7.x,  v7.y,  v7.z,   left_color.x, left_color.y, left_color.z, // v7
			   v3.x,  v3.y,  v3.z,   left_color.x, left_color.y, left_color.z, // v3

			   //////
			   // back

				v4.x,  v4.y,  v4.z,   back_color.x, back_color.y, back_color.z, // v4
				v5.x,  v5.y,  v5.z,   back_color.x, back_color.y, back_color.z, // v5
				v6.x,  v6.y,  v6.z,   back_color.x, back_color.y, back_color.z, // v6

				v4.x,  v4.y,  v4.z,   back_color.x, back_color.y, back_color.z, // v4
				v6.x,  v6.y,  v6.z,   back_color.x, back_color.y, back_color.z, // v6
				v7.x,  v7.y,  v7.z,   back_color.x, back_color.y, back_color.z, // v7

				//////
				// top

				 v6.x,  v6.y,  v6.z,   top_color.x, top_color.y, top_color.z, // v6
				 v2.x,  v2.y,  v2.z,   top_color.x, top_color.y, top_color.z, // v2
				 v3.x,  v3.y,  v3.z,   top_color.x, top_color.y, top_color.z, // v3

				 v6.x,  v6.y,  v6.z,   top_color.x, top_color.y, top_color.z, // v6
				 v7.x,  v7.y,  v7.z,   top_color.x, top_color.y, top_color.z, // v7
				 v3.x,  v3.y,  v3.z,   top_color.x, top_color.y, top_color.z, // v3

				 /////
				 // bottom

				  v0.x,  v0.y,  v0.z,   bottom_color.x, bottom_color.y, bottom_color.z, // v0
				  v1.x,  v1.y,  v1.z,   bottom_color.x, bottom_color.y, bottom_color.z, // v1
				  v5.x,  v5.y,  v5.z,   bottom_color.x, bottom_color.y, bottom_color.z, // v5

				  v0.x,  v0.y,  v0.z,   bottom_color.x, bottom_color.y, bottom_color.z, // v0
				  v4.x,  v4.y,  v4.z,   bottom_color.x, bottom_color.y, bottom_color.z, // v4
				  v5.x,  v5.y,  v5.z,   bottom_color.x, bottom_color.y, bottom_color.z  // v5
		};

		m_test_cube_vbo->update(test_cube_data, sizeof(test_cube_data), sizeof(test_cube_data) * i);
	}

}

void CubeRenderer::render()
{
	m_test_cube_vao->bind();
	m_test_cube_vbo->bind();

	OpenGL::Renderer::drawArrays(*m_test_cube_vao, DrawUsage::TRIANGLE, m_cube_positions.size() * 3 * 2 * 6);
}
