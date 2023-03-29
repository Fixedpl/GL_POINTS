#include "ComputeShaderPointRenderer.h"

#include "OpenGL/GL_gl.h"
#include "OpenGL/GL_Renderer.h"

ComputeShaderPointRenderer::ComputeShaderPointRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	m_screen_width(screen_width),
	m_screen_height(screen_height)
{

}

ComputeShaderPointRenderer::~ComputeShaderPointRenderer()
{
	delete m_tex_quad_vao;
	delete m_tex_quad_vbo;
	delete m_tex_quad_layout;

	delete m_compute_shader;
	delete m_texture_shader;
}

void ComputeShaderPointRenderer::addPointAt(const glm::vec3& pos)
{
	m_points.push_back({ pos, m_default_color });
}

void ComputeShaderPointRenderer::addPointAt(const glm::vec3& pos, const glm::vec3& color)
{
	m_points.push_back({ pos, color });
}

void ComputeShaderPointRenderer::init()
{
	m_compute_shader = new OpenGL::ComputeShader("res/shaders/Compute_shader_c.glsl");
	m_texture_shader = new OpenGL::Shader("res/shaders/Compute_shader_v.glsl", "res/shaders/Compute_shader_f.glsl");
	m_texture_shader->bind();
	m_texture_shader->setUniform1i("tex", 0);

	m_tex_quad_vao = new OpenGL::VertexArray();
	m_tex_quad_vao->bind();

	m_tex_quad_vbo = new OpenGL::VertexBuffer(sizeof(float) * 6 * 5, DrawType::STATIC);
	m_tex_quad_layout = new OpenGL::BufferLayout();
	m_tex_quad_layout->addAttribute<float>(3);
	m_tex_quad_layout->addAttribute<float>(2);

	m_tex_quad_vao->addVertexBuffer(m_tex_quad_vbo);
	m_tex_quad_vao->setBufferLayout(*m_tex_quad_layout);

	float quad_buffer[6 * 5] {
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,

		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f
	};

	m_tex_quad_vbo->update(quad_buffer, sizeof(float) * 6 * 5, 0);

	unsigned int texture;

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_screen_width, m_screen_height, 0, GL_RGBA,
		GL_FLOAT, NULL);

	glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F);
}

void ComputeShaderPointRenderer::render()
{
	m_compute_shader->bind();

	glDispatchCompute((unsigned int)m_screen_width, (unsigned int)m_screen_height, 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	m_texture_shader->bind();
	m_tex_quad_vao->bind();
	m_tex_quad_vbo->bind();

	OpenGL::Renderer::drawArrays(*m_tex_quad_vao, DrawUsage::POINT, m_points.size());
}
