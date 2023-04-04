#include "PointCloudTestingEnv.h"

#include <imgui/imgui.h>
#include <implot/implot.h>

#include "PointCloudApplication.h"


PointCloudTestingEnv::PointCloudTestingEnv(PointCloudApplication* app, 
	std::vector<PointData>& point_cloud, const glm::vec3& starting_pos, std::function<void()> on_close)
	:
	m_fps_data(m_seconds_measured / m_polling_rate),
	m_time_elapsed(0.0f),
	m_tick(0),
	m_app(app),
	m_starting_camera_pos(starting_pos),
	m_point_cloud(point_cloud),
	m_on_close(on_close)
{
	init();
}

void PointCloudTestingEnv::init()
{
	m_render_methods = {
		{ "GL_POINTS" },
		{ "Basic" },
		{ "Z-buffer" },
		{ "Early z" }
	};

	glm::vec2 screen_size = m_app->getWindowSize();
	m_camera = new PerspectiveCamera(screen_size.x, screen_size.y, m_starting_camera_pos);

}

void PointCloudTestingEnv::onUpdate(const float& dt)
{
	m_time_elapsed += dt;
}

void PointCloudTestingEnv::onImGuiUpdate()
{
	ImGui::Begin("Choose rendering method");

	if (ImGui::Button("<-")) {
		m_on_close();
	}

	ImGui::BeginListBox("Method");
	for (auto& method : m_render_methods) {
		if (ImGui::Selectable(method.label.c_str())) {

		}
	}
	ImGui::EndListBox();

	imGuiFps();

	ImGui::End();
}

void PointCloudTestingEnv::handleMouseMovement()
{
	glm::vec2 mouse_pos = m_app->getMouse()->getLastCursorPosition();
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
	m_camera->front() = glm::normalize(direction);
	m_camera->updateMatrix();
}

void PointCloudTestingEnv::handleKeyboardMovement(const float& dt)
{
	if (m_app->getKeyboard()->isKeyPressed(KeyCode::KEY_W)) {
		m_camera->position() += dt * m_movement_speed * m_camera->front();
		m_camera->updateMatrix();
	}
	if (m_app->getKeyboard()->isKeyPressed(KeyCode::KEY_S)) {
		m_camera->position() -= dt * m_movement_speed * m_camera->front();
		m_camera->updateMatrix();
	}
	if (m_app->getKeyboard()->isKeyPressed(KeyCode::KEY_A)) {
		m_camera->position() -= dt * glm::normalize(glm::cross(m_camera->front(), m_camera->up())) * m_movement_speed;
		m_camera->updateMatrix();
	}
	if (m_app->getKeyboard()->isKeyPressed(KeyCode::KEY_D)) {
		m_camera->position() += dt * glm::normalize(glm::cross(m_camera->front(), m_camera->up())) * m_movement_speed;
		m_camera->updateMatrix();
	}
}

void PointCloudTestingEnv::imGuiFps()
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
			std::max(0.0f, m_time_elapsed - m_seconds_measured),
			std::max(m_seconds_measured - 2 * m_polling_rate,
				m_time_elapsed - 2 * m_polling_rate),
			0,
			30,
			ImPlotCond_Always
		);
		ImPlot::PlotLine("f(x)", m_fps_data.x(), m_fps_data.y(), m_fps_data.size(), ImPlotFlags_::ImPlotFlags_None, m_fps_data.offset());
		ImPlot::EndPlot();
	}
}

void PointCloudTestingEnv::onEvent(const float& dt)
{
	handleMouseMovement();
	handleKeyboardMovement(dt);
}
