#include "CSEarlyZRenderer.h"


CSEarlyZRenderer::CSEarlyZRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	ComputeShaderPointRenderer(screen_width, screen_height)
{
}

void CSEarlyZRenderer::init(const std::vector<PointData>& point_data)
{
	prepareComputeShader();
	preparePointsSSBO(point_data);
	prepareDepthSSBO();
	prepareTextureBuffers();
}

void CSEarlyZRenderer::render(const glm::mat4& mvp)
{
	executeComputeShader(mvp);
	renderAndClearTexture();
	clearDepthBuffer();
}

void CSEarlyZRenderer::cleanup()
{
	cleanupPointsSSBO();
	cleanupDepthSSBO();
	cleanupTextureBuffers();
	cleanupComputeShader();
}

void CSEarlyZRenderer::prepareComputeShader()
{
	m_compute_shader = new OpenGL::ComputeShader("res/shaders/Compute_shader_early_z_c.glsl");
	m_compute_shader->bind();
	m_compute_shader->setUniform2i("u_image_size", glm::vec2(m_screen_width, m_screen_height));
}
