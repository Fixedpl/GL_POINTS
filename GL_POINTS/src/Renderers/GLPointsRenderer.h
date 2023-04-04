#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"

#include "PointData.h"
#include "PointRenderer.h"


class GLPointsRenderer : public PointRenderer
{
public:

	void init(const std::vector<PointData>& point_data) override;

	void render(const glm::mat4& mvp) override;

	void cleanup() override;

private:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	uint32_t m_point_count;

	OpenGL::Shader* m_shader;

	OpenGL::VertexArray* m_points_vao;
	OpenGL::VertexBuffer* m_points_vbo;
	OpenGL::BufferLayout* m_points_layout;

};

