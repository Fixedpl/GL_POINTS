#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"

#include "PointData.h"


class BasicPointRenderer
{
public:

	~BasicPointRenderer();

	void addPointAt(const glm::vec3& pos);
	void addPointAt(const glm::vec3& pos, const glm::vec3& color);

	void init();

	void render();

private:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	std::vector<PointData> m_points;

	OpenGL::Shader* m_shader;

	OpenGL::VertexArray* m_points_vao;
	OpenGL::VertexBuffer* m_points_vbo;
	OpenGL::BufferLayout* m_points_layout;

};

