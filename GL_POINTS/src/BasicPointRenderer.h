#pragma once
#include "Application.h"

#include "OpenGL/GL_Shader.h"
#include "OpenGL/GL_VertexBuffer.h"
#include "OpenGL/GL_IndexBuffer.h"

#include "Camera.h"
#include "CubeRenderer.h"
#include "PointRenderer.h"


class FPSData
{
public:

	FPSData(const uint32_t& size) {
		m_current_size = 0;
		m_max_size = size;
		m_offset = 0;
		m_x = new float[m_max_size] { 0 };
		m_y = new float[m_max_size] { 0 };
	}

	~FPSData() {
		delete[] m_x;
		delete[] m_y;
	}

	void add(const float& x_val, const float& y_val) {
		m_x[m_it] = x_val;
		m_y[m_it] = y_val;
		m_it = (m_it + 1) % m_max_size;
		m_current_size = std::min(m_max_size, m_current_size + 1);
		m_offset = m_current_size < m_max_size ? 0 : m_it;
	}

	float* x() {
		return m_x;
	}

	float* y() {
		return m_y;
	}

	uint32_t size() {
		return m_current_size;
	}

	uint32_t offset() {
		return m_offset;
	}

private:

	float* m_x;
	float* m_y;

	uint32_t m_max_size;
	uint32_t m_current_size;
	
	uint32_t m_it;
	uint32_t m_offset;
};


class BasicPointRenderer : public Application
{
public:

	BasicPointRenderer(WindowSettings window_settings, 
		const std::string& point_cloud_path, 
		const glm::vec3& camera_pos);

	void beforeUpdate() override;

	void onEvent(const float& dt) override;

	void onUpdate(const float& dt) override;

	void onImGuiUpdate() override;

private:

	void init();
	void initPoints();
	void initTestCube();

	void handleMouse();
	void handleMouseMovement();
	void handleMouseSceneFocus();

	void handleKeyboard(const float& dt);
	void handleKeyboardMovement(const float& dt);
	void handleKeyboardSceneFocus();

	void setFlyingMode(const bool& value);

private:

	std::string m_point_cloud_path;

	OpenGL::Shader m_shader;

	const float m_default_fov = 60.0f;
	float m_fov;

	const bool m_default_flying_mode = true;
	bool m_flying_mode;
	

	const glm::vec3 m_starting_camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	PerspectiveCamera m_camera;

	const float m_movement_speed = 1.0f;

	// Mouse related
	bool m_first_mouse_move;
	glm::vec2 m_last_mouse_pos;
	float m_yaw;
	float m_pitch;

	PointRenderer m_point_renderer;
	CubeRenderer m_cube_renderer;

	const float m_seconds_measured = 2.0f;
	const float m_polling_rate = 0.05f;

	float m_time_elapsed;
	uint32_t m_tick;
	FPSData m_fps_data;

};

