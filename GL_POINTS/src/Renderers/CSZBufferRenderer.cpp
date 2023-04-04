#include "CSZBufferRenderer.h"

CSZBufferRenderer::CSZBufferRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	ComputeShaderPointRenderer(screen_width, screen_height)
{
}

void CSZBufferRenderer::init(const std::vector<PointData>& point_data)
{
	prepareComputeShader();
	preparePointsSSBO(point_data);
	prepareDepthSSBO();
	prepareTextureBuffers();
}

void CSZBufferRenderer::render(const glm::mat4& mvp)
{
	executeComputeShader(mvp);
	renderAndClearTexture();
	clearDepthBuffer();
}

void CSZBufferRenderer::cleanup()
{
	cleanupPointsSSBO();
	cleanupDepthSSBO();
	cleanupTextureBuffers();
	cleanupComputeShader();
}

void CSZBufferRenderer::prepareComputeShader()
{
	m_compute_shader = new OpenGL::ComputeShader("res/shaders/Compute_shader_z_buffer_c.glsl");
	m_compute_shader->bind();
	m_compute_shader->setUniform2i("u_image_size", glm::vec2(m_screen_width, m_screen_height));
}
