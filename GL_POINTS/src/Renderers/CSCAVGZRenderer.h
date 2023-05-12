#pragma once
#include <vector>

#include "OpenGL/GL_VertexBuffer.h"
#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_ComputeShader.h"

#include "PointRenderer.h"



class CSCAVGZRenderer : public PointRenderer
{
public:

	CSCAVGZRenderer(const uint32_t& screen_width, const uint32_t& screen_height);

protected:

	void init(const std::vector<PointData>& point_data);

	void render(const glm::mat4& mvp);

	void cleanup();

	void prepareComputeShader();

	void preparePointsSSBO(const std::vector<PointData>& point_data);
	void prepareDepthSSBO();
	void prepareColorSSBO();
	void prepareTextureBuffers();

	void executeComputeShader(const glm::mat4& mvp);
	void renderAndClearTexture();
	void clearDepthBuffer();
	void clearColorBuffer();

	void cleanupPointsSSBO();
	void cleanupDepthSSBO();
	void cleanupColorSSBO();
	void cleanupTextureBuffers();
	void cleanupComputeShader();

protected:

	const glm::vec3 m_default_color = glm::vec3(255.0f, 255.0f, 128.0f);

	uint32_t m_screen_width;
	uint32_t m_screen_height;

	OpenGL::Shader* m_texture_shader;
	OpenGL::ComputeShader* m_depth_shader;
	OpenGL::ComputeShader* m_color_shader;
	OpenGL::ComputeShader* m_final_shader;

	OpenGL::VertexArray* m_tex_quad_vao;
	OpenGL::VertexBuffer* m_tex_quad_vbo;
	OpenGL::BufferLayout* m_tex_quad_layout;

	uint32_t m_texture;

	uint32_t m_points_ssbo;
	uint32_t m_depth_ssbo;
	uint32_t m_color_ssbo;

	int32_t m_num_work_groups;
	const glm::vec2 m_work_group_size = glm::vec2(32);
};

