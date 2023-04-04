#include "PointCloudApplication.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>

#include "lasreader.hpp"
#include "laswriter.hpp"

#include "OpenGL/GL_Renderer.h"

#include "Core/MouseInput.h"
#include "Core/KeyboardInput.h"

#include "PointCloudHelper.h"
#include "EmptyPointRenderer.h"







PointCloudApplication::PointCloudApplication(WindowSettings window_settings, 
	const std::vector<PointCloudSetup>& setups)
	: 
	Application(window_settings),
	m_hide_cursor(false),
	m_menu_screen_view(true),
	m_setups(setups),
	m_test_env_close_request(false)
{
}

PointCloudApplication::~PointCloudApplication()
{
	delete m_testing_env;
}

void PointCloudApplication::beforeUpdate()
{
	init();
}

void PointCloudApplication::onEvent(const float& delta)
{
	handleMouse();

	handleKeyboard(delta);

	if (!m_menu_screen_view) {
		m_testing_env->onEvent(delta);
	}
}

void PointCloudApplication::onUpdate(const float& dt)
{
	if (!m_menu_screen_view) {
		m_testing_env->onUpdate(dt);
	}
}

void PointCloudApplication::onImGuiUpdate()
{
	if (m_menu_screen_view) {
		ImGui::Begin("Choose point cloud");

		for (auto& setup : m_setups) {
			if (ImGui::Button(setup.label.c_str())) {
				loadPoints(setup.path);
				m_menu_screen_view = false;

				m_testing_env = new PointCloudTestingEnv(
					this, 
					m_point_cloud, 
					setup.starting_camera_pos,
					[this]() {
						this->m_test_env_close_request = true;
					}
				);
			}
		}

		ImGui::End();
	} else {
		m_testing_env->onImGuiUpdate();
		if (m_test_env_close_request) {
			handleTestEnvClose();
		}
	}
}

void PointCloudApplication::loadPoints(const std::string& path)
{
	LASreadOpener* las_read_opener = new LASreadOpener();
	LASreader* las_reader = las_read_opener->open(path.c_str());

	while (las_reader->read_point()) {
		LASpoint& point = las_reader->point;

		F64 x = las_reader->get_x();
		F64 y = las_reader->get_y();
		F64 z = las_reader->get_z();

		F64 r = point.get_R() / 256.0f;
		F64 g = point.get_G() / 256.0f;
		F64 b = point.get_B() / 256.0f;

		m_point_cloud.push_back(PointData({ x, y, z }, { r, g, b }));
	}
}

void PointCloudApplication::init()
{
	hideCursor(false);
}

void PointCloudApplication::handleMouse()
{
	handleMouseSceneFocus();
}

void PointCloudApplication::handleMouseSceneFocus()
{
	if (m_mouse->isRightButtonPressed()) {
		hideCursor(true);
	}
}

void PointCloudApplication::handleKeyboard(const float& dt)
{
	handleKeyboardSceneFocus();
}

void PointCloudApplication::handleKeyboardSceneFocus()
{
	if (m_keyboard->isKeyPressed(KeyCode::KEY_ESCAPE)) {
		hideCursor(false);
	}
}

void PointCloudApplication::hideCursor(const bool& value)
{
	m_hide_cursor = value;
	if (m_hide_cursor) {
		getWindow().setCursorFocused(true);
	} else {
		getWindow().setCursorFocused(false);
	}
}

KeyboardInput* PointCloudApplication::getKeyboard()
{
	return m_keyboard;
}

MouseInput* PointCloudApplication::getMouse()
{
	return m_mouse;
}

glm::vec2 PointCloudApplication::getWindowSize()
{
	WindowSettings window_settings = getWindow().getWindowSettings();
	return glm::vec2(window_settings.width, window_settings.height);
}

void PointCloudApplication::handleTestEnvClose()
{
	m_menu_screen_view = true;
	delete m_testing_env;
}