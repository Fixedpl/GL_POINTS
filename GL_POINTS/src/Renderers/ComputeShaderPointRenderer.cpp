#include "ComputeShaderPointRenderer.h"

#include "OpenGL/GL_gl.h"
#include "OpenGL/GL_Renderer.h"



ComputeShaderPointRenderer::ComputeShaderPointRenderer(const uint32_t& screen_width, const uint32_t& screen_height)
	:
	m_screen_width(screen_width),
	m_screen_height(screen_height)
{
}

void ComputeShaderPointRenderer::preparePointsSSBO(const std::vector<PointData>& point_data)
{
	uint32_t point_count = point_data.size();

	uint32_t work_group_size_squared = std::ceil((float)point_count / (m_work_group_size.x * m_work_group_size.y));
	m_num_work_groups = std::ceil(std::sqrt(work_group_size_squared));

	uint32_t point_count_with_fill = m_num_work_groups * m_num_work_groups * m_work_group_size.x * m_work_group_size.y;

	float* points_data = new float[point_count_with_fill * 6] {};

	for (uint32_t i = 0; i < point_count; i++) {
		points_data[i * 6 + 0] = point_data[i].position.x;
		points_data[i * 6 + 1] = point_data[i].position.y;
		points_data[i * 6 + 2] = point_data[i].position.z;

		points_data[i * 6 + 3] = point_data[i].color.r;
		points_data[i * 6 + 4] = point_data[i].color.g;
		points_data[i * 6 + 5] = point_data[i].color.b;
	}

	glGenBuffers(1, &m_points_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_points_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, point_count_with_fill * 6 * sizeof(float), points_data, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, m_points_ssbo);

	delete[] points_data;
}

void ComputeShaderPointRenderer::prepareDepthSSBO()
{
	glGenBuffers(1, &m_depth_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_depth_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_screen_width * m_screen_height * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_depth_ssbo);
}

void ComputeShaderPointRenderer::prepareTextureBuffers()
{
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

	float quad_buffer[6 * 5]{
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,

		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f
	};

	m_tex_quad_vbo->update(quad_buffer, sizeof(float) * 6 * 5, 0);


	glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_screen_width, m_screen_height, 0, GL_RGBA,
		GL_FLOAT, NULL);

	glBindImageTexture(0, m_texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void ComputeShaderPointRenderer::executeComputeShader(const glm::mat4& mvp)
{
	m_compute_shader->bind();
	m_compute_shader->setUniformMat4f("u_MVP", mvp);

	glDispatchCompute((unsigned int)m_num_work_groups, (unsigned int)m_num_work_groups, 1);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeShaderPointRenderer::renderAndClearTexture()
{
	m_texture_shader->bind();
	m_tex_quad_vao->bind();

	OpenGL::Renderer::drawArrays(*m_tex_quad_vao, DrawUsage::TRIANGLE, 6);

	float default_texture_color[4] = {
		0.5f, 0.65f, 1.0f, 1.0f
	};

	glClearTexImage(m_texture, 0, GL_RGBA, GL_FLOAT, &default_texture_color);
}

void ComputeShaderPointRenderer::clearDepthBuffer()
{
	float one = -1.0f;
	unsigned int float_as_uint;
	memcpy(&float_as_uint, &one, 4);
	glClearBufferData(GL_SHADER_STORAGE_BUFFER, GL_R32UI, GL_RED, GL_UNSIGNED_INT, &float_as_uint);

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void ComputeShaderPointRenderer::cleanupPointsSSBO()
{
	glDeleteBuffers(1, &m_points_ssbo);
}

void ComputeShaderPointRenderer::cleanupDepthSSBO()
{
	glDeleteBuffers(1, &m_depth_ssbo);
}

void ComputeShaderPointRenderer::cleanupTextureBuffers()
{
	glDeleteTextures(1, &m_texture);

	delete m_tex_quad_vao;
	delete m_tex_quad_vbo;
	delete m_tex_quad_layout;

	delete m_texture_shader;
}

void ComputeShaderPointRenderer::cleanupComputeShader()
{
	delete m_compute_shader;
}
