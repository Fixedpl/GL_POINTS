#include "ComputeShaderPointRenderer.h"

#include "OpenGL/GL_gl.h"

ComputeShaderPointRenderer::ComputeShaderPointRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	m_screen_width(screen_width),
	m_screen_height(screen_height)
{

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
	m_compute_shader->loadShader("res/shaders/Compute_shader_c.glsl");
	m_texture_shader->loadShader("res/shaders/Compute_shader_v.glsl", "res/shaders/Compute_shader_f.glsl");


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

}
