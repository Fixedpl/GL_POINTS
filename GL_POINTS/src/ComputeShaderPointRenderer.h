#pragma once
#include <vector>

#include "OpenGL/GL_VertexBuffer.h"
#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_ComputeShader.h"

#include "PointRenderer.h"
#include "PointData.h"


class ComputeShaderPointRenderer : public PointRenderer
{
public:

	ComputeShaderPointRenderer(const uint32_t& screen_width, const uint32_t& screen_height);

	void init(const std::vector<PointData>& point_data) override;

	void render(const glm::mat4& mvp) override;

	void cleanup() override;

	void setNumWorkGroups(const int32_t& num_work_groups);

private:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	uint32_t m_screen_width;
	uint32_t m_screen_height;

	OpenGL::Shader* m_texture_shader;
	OpenGL::ComputeShader* m_compute_shader;

	OpenGL::VertexArray* m_tex_quad_vao;
	OpenGL::VertexBuffer* m_tex_quad_vbo;
	OpenGL::BufferLayout* m_tex_quad_layout;

	uint32_t m_texture;

	uint32_t m_points_ssbo;
	uint32_t m_depth_ssbo;

	int32_t m_num_work_groups;
	const glm::vec2 m_work_group_size = glm::vec2(32);
};

