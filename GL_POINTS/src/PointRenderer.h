#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"


struct PointData
{
	PointData(const glm::vec3& _position, const glm::vec3& _color) 
		: position(_position), color(_color) {}

	glm::vec3 position;
	glm::vec3 color;
};


class PointRenderer
{
public:

	void addPointAt(const glm::vec3& pos);
	void addPointAt(const glm::vec3& pos, const glm::vec3& color);

	void init();

	void render();

private:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	std::vector<PointData> m_points;

	OpenGL::VertexArray* m_points_vao;
	OpenGL::VertexBuffer* m_points_vbo;
	OpenGL::BufferLayout* m_points_layout;

};

