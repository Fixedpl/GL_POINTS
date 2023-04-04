#pragma once
#include <string>
#include <vector>
#include <functional>

#include <glm/glm.hpp>

#include "Core/Camera.h"
#include "Core/KeyboardInput.h"
#include "Core/MouseInput.h"

#include "PointData.h"
#include "PointRenderer.h"


class PointCloudApplication;

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


struct RenderMethod
{
	std::string label;
	PointRenderer* renderer;
};


class PointCloudTestingEnv
{
public:

	PointCloudTestingEnv(PointCloudApplication* app, std::vector<PointData>& point_cloud, 
		const glm::vec3& starting_pos, std::function<void()> on_close);
	~PointCloudTestingEnv();

	void onUpdate(const float& dt);

	void onImGuiUpdate();

	void onEvent(const float& dt);

private:

	void init();

	void handleMouseMovement();
	void handleKeyboardMovement(const float& dt);

	void imGuiFps();

private:

	std::vector<RenderMethod> m_render_methods;

	const float m_seconds_measured = 2.0f;
	const float m_polling_rate = 0.05f;

	float m_time_elapsed;
	uint32_t m_tick;
	FPSData m_fps_data;

	const bool m_default_flying_mode = true;
	bool m_flying_mode;


	glm::vec3 m_starting_camera_pos;
	PerspectiveCamera* m_camera;

	const float m_movement_speed = 1.0f;

	// Mouse related
	bool m_first_mouse_move;
	glm::vec2 m_last_mouse_pos;
	float m_yaw = -90.0f;
	float m_pitch;

	PointCloudApplication* m_app;
	std::vector<PointData> m_point_cloud;

	std::function<void()> m_on_close;

	PointRenderer* m_empty_renderer;
	PointRenderer* m_current_renderer;

};