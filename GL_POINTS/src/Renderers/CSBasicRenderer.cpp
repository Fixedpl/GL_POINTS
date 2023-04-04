#include "CSBasicRenderer.h"

CSBasicRenderer::CSBasicRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	ComputeShaderPointRenderer(screen_width, screen_height)
{
}

void CSBasicRenderer::init(const std::vector<PointData>& point_data)
{
	prepareComputeShader();
	preparePointsSSBO(point_data);
	prepareTextureBuffers();
}

void CSBasicRenderer::render(const glm::mat4& mvp)
{
	executeComputeShader(mvp);
	renderAndClearTexture();
}

void CSBasicRenderer::cleanup()
{
	cleanupPointsSSBO();
	cleanupTextureBuffers();
	cleanupComputeShader();
}

void CSBasicRenderer::prepareComputeShader()
{
	m_compute_shader = new OpenGL::ComputeShader("res/shaders/Compute_shader_basic_c.glsl");
	m_compute_shader->bind();
	m_compute_shader->setUniform2i("u_image_size", glm::vec2(m_screen_width, m_screen_height));
}
