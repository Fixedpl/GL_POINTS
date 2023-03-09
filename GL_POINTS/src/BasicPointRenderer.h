#pragma once
#include "Application.h"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"
#include "OpenGL/GL_IndexBuffer.h"

#include "Camera.h"
#include "CubeRenderer.h"

class BasicPointRenderer : public Application
{
public:

	BasicPointRenderer(WindowSettings window_settings);

	void beforeUpdate() override;

	void onEvent(const float& dt) override;

	void onUpdate(const float& dt) override;

private:

	void init();
	void initTestCube();

	void handleMouseMovement();
	void handleKeyboard(const float& dt);

private:

	OpenGL::Shader m_shader;

	const glm::vec3 m_starting_camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	PerspectiveCamera m_camera;

	const float m_movement_speed = 10.0f;

	// Mouse related
	bool m_first_mouse_move;
	glm::vec2 m_last_mouse_pos;
	float m_yaw;
	float m_pitch;

	CubeRenderer m_cube_renderer;

};

