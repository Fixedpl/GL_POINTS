#include "PointCloudApplication.h"

#include <imgui/imgui.h>
#include <implot/implot.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>

#include "PointCloudHelper.h"

#include "lasreader.hpp"
#include "laswriter.hpp"

#include "OpenGL/GL_Renderer.h"

#include "MouseInput.h"
#include "KeyboardInput.h"



PointCloudApplication::PointCloudApplication(WindowSettings window_settings, 
	const std::string& point_cloud_path, 
	const glm::vec3& camera_pos)
	: 
	Application(window_settings),
	m_fov(m_default_fov),
	m_flying_mode(m_default_flying_mode),
	m_time_elapsed(0.0f),
	m_camera(
		window_settings.width, 
		window_settings.height, 
		glm::vec3(0.0f),
		m_fov
	),
	m_fps_data(m_seconds_measured / m_polling_rate),
	m_tick(0),
	m_point_cloud_path(point_cloud_path)
{
}

void PointCloudApplication::beforeUpdate()
{
	init();
}

void PointCloudApplication::onEvent(const float& delta)
{
	handleMouse();

	handleKeyboard(delta);
}

void PointCloudApplication::onUpdate(const float& dt)
{
	m_time_elapsed += dt;
	m_shader.setUniformMat4f("u_MVP", m_camera.matrix());
	m_cube_renderer.render();
	//m_point_renderer.render();
}

void PointCloudApplication::onImGuiUpdate()
{
	float imgui_framerate = ImGui::GetIO().Framerate;
	float ms_per_frame = 1000.0f / imgui_framerate;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", ms_per_frame, imgui_framerate);
	if (m_time_elapsed - (m_tick * m_polling_rate) >= m_polling_rate * (m_tick + 1)) {
		m_fps_data.add(m_time_elapsed, ms_per_frame);
		m_tick++;
	}

	if (ImPlot::BeginPlot("Line Plots", ImVec2(400, 200))) {
		ImPlot::SetupAxes("FPS", "t");
		ImPlot::SetupAxesLimits(
			max(0.0f, m_time_elapsed - m_seconds_measured), 
			max(m_seconds_measured - 2 * m_polling_rate, 
				m_time_elapsed - 2 * m_polling_rate), 
			0, 
			30, 
			ImPlotCond_Always
		);
		ImPlot::PlotLine("f(x)", m_fps_data.x(), m_fps_data.y(), m_fps_data.size(), ImPlotFlags_::ImPlotFlags_None, m_fps_data.offset());
		ImPlot::EndPlot();
	}

	ImGui::SliderFloat("FOV", &m_fov, 0.0f, 120.0f);
	m_camera.fov() = m_fov;
	m_camera.updatePerspectiveMatrix();
	m_camera.updateMatrix();
}

void PointCloudApplication::init()
{
	setFlyingMode(false);

	m_shader.setUniformMat4f("u_MVP", m_camera.matrix());

	m_first_mouse_move = true;

	initTestCube();

	//initPoints();

}

void PointCloudApplication::initPoints()
{
	{
		LASreadOpener* las_read_opener = new LASreadOpener();
		LASreader* las_reader = las_read_opener->open(m_point_cloud_path.c_str());

		while (las_reader->read_point()) {
			LASpoint& point = las_reader->point;

			F64 x = las_reader->get_x();
			F64 y = las_reader->get_y();
			F64 z = las_reader->get_z();

			F64 r = point.get_R() / 256.0f;
			F64 g = point.get_G() / 256.0f;
			F64 b = point.get_B() / 256.0f;

			m_point_renderer.addPointAt({ x, y, z }, { r, g, b });
		}
	}

	m_point_renderer.init();
}

void PointCloudApplication::initTestCube()
{
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  0.0f,  5.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  0.0f, -5.0f));

	m_cube_renderer.addCubeAt(glm::vec3(-5.0f,  0.0f,  0.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 5.0f,  0.0f,  0.0f));

	m_cube_renderer.addCubeAt(glm::vec3( 0.0f, -5.0f, 0.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  5.0f, 0.0f));

	m_cube_renderer.init();
}

void PointCloudApplication::handleMouse()
{
	if (m_flying_mode) {
		handleMouseMovement();
	}
	handleMouseSceneFocus();
}

void PointCloudApplication::handleMouseMovement()
{
	glm::vec2 mouse_pos = m_mouse->getLastCursorPosition();
	if (m_first_mouse_move)
	{
		m_last_mouse_pos = mouse_pos;
		m_first_mouse_move = false;
	}

	glm::vec2 offset = glm::vec2(
		mouse_pos.x - m_last_mouse_pos.x, 
		m_last_mouse_pos.y - mouse_pos.y
	);

	m_last_mouse_pos = mouse_pos;

	float sensitivity = 0.2f;
	offset *= sensitivity;

	m_yaw += offset.x;
	m_pitch += offset.y;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_camera.front() = glm::normalize(direction);
	m_camera.updateMatrix();
}

void PointCloudApplication::handleMouseSceneFocus()
{
	if (m_mouse->isRightButtonPressed()) {
		setFlyingMode(true);
	}
}

void PointCloudApplication::handleKeyboard(const float& dt)
{
	if (m_flying_mode) {
		handleKeyboardMovement(dt);
	}
	handleKeyboardSceneFocus();
}

void PointCloudApplication::handleKeyboardMovement(const float& dt)
{
	if (m_keyboard->isKeyPressed(KeyCode::KEY_W)) {
		m_camera.position() += dt * m_movement_speed * m_camera.front();
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_S)) {
		m_camera.position() -= dt * m_movement_speed * m_camera.front();
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_A)) {
		m_camera.position() -= dt * glm::normalize(glm::cross(m_camera.front(), m_camera.up())) * m_movement_speed;
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_D)) {
		m_camera.position() += dt * glm::normalize(glm::cross(m_camera.front(), m_camera.up())) * m_movement_speed;
		m_camera.updateMatrix();
	}
}

void PointCloudApplication::handleKeyboardSceneFocus()
{
	if (m_keyboard->isKeyPressed(KeyCode::KEY_ESCAPE)) {
		setFlyingMode(false);
	}
}

void PointCloudApplication::setFlyingMode(const bool& value)
{
	m_flying_mode = value;
	if (m_flying_mode) {
		getWindow().setCursorFocused(true);
	} else {
		getWindow().setCursorFocused(false);
	}
}
