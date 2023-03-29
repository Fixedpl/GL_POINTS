#include "BasicPointRenderer.h"

#include "OpenGL/GL_Renderer.h"

BasicPointRenderer::~BasicPointRenderer()
{
	delete m_points_vao;
	delete m_points_vbo;
	delete m_points_layout;
	delete m_shader;
}

void BasicPointRenderer::addPointAt(const glm::vec3& pos)
{
	m_points.push_back({ pos, m_default_color });
}

void BasicPointRenderer::addPointAt(const glm::vec3& pos, const glm::vec3& color)
{
	m_points.push_back({ pos, color });
}

void BasicPointRenderer::init()
{
	m_shader = new OpenGL::Shader("res/shaders/GL_POINTS_v.glsl", "res/shaders/GL_POINTS_f.glsl");
	m_shader->bind();

	m_points_vao = new OpenGL::VertexArray();
	m_points_vao->bind();

	m_points_vbo = new OpenGL::VertexBuffer(sizeof(PointData) * m_points.size(), DrawType::STATIC);
	m_points_layout = new OpenGL::BufferLayout();
	m_points_layout->addAttribute<float>(3);
	m_points_layout->addAttribute<float>(3);

	m_points_vao->addVertexBuffer(m_points_vbo);
	m_points_vao->setBufferLayout(*m_points_layout);

	float* points_buffer = new float[m_points.size() * 6];

	for (int i = 0; i < m_points.size(); i++) {
		PointData point = m_points[i];

		points_buffer[i * 6 + 0] = point.position.x;
		points_buffer[i * 6 + 1] = point.position.y;
		points_buffer[i * 6 + 2] = point.position.z;

		points_buffer[i * 6 + 3] = point.color.r;
		points_buffer[i * 6 + 4] = point.color.g;
		points_buffer[i * 6 + 5] = point.color.b;
	}

	m_points_vbo->update(points_buffer, sizeof(PointData) * m_points.size(), 0);

	delete[] points_buffer;
}

void BasicPointRenderer::render()
{
	m_shader->bind();
	m_points_vao->bind();
	m_points_vbo->bind();

	OpenGL::Renderer::drawArrays(*m_points_vao, DrawUsage::POINT, m_points.size());
}
