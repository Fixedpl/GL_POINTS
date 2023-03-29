#pragma once
#include <vector>

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_ComputeShader.h"

#include "PointData.h"



class ComputeShaderPointRenderer
{
public:

	ComputeShaderPointRenderer(const uint32_t& screen_width, const uint32_t& screen_height);

	void addPointAt(const glm::vec3& pos);
	void addPointAt(const glm::vec3& pos, const glm::vec3& color);

	void init();

	void render();

private:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	std::vector<PointData> m_points;

	uint32_t m_screen_width;
	uint32_t m_screen_height;

	OpenGL::Shader* m_texture_shader;
	OpenGL::ComputeShader* m_compute_shader;

};

