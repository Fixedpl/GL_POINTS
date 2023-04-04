#pragma once
#include "Core/Application.h"

#include "PointCloudTestingEnv.h"




struct PointCloudSetup
{
	std::string label;
	std::string path;
	glm::vec3 starting_camera_pos;
};

class PointCloudApplication : public Application
{
public:

	PointCloudApplication(WindowSettings window_settings, 
		const std::vector<PointCloudSetup>& setups);
	~PointCloudApplication();

	void beforeUpdate() override;

	void onEvent(const float& dt) override;

	void onUpdate(const float& dt) override;

	void onImGuiUpdate() override;

	KeyboardInput* getKeyboard();

	MouseInput* getMouse();

	glm::vec2 getWindowSize();

	void hideCursor(const bool& value);

private:

	void loadPoints(const std::string& path);

	void init();

	void handleTestEnvClose();

private:

	std::vector<PointCloudSetup> m_setups;

	std::vector<PointData> m_point_cloud;

	bool m_menu_screen_view;

	bool m_hide_cursor;

	PointCloudTestingEnv* m_testing_env;
	bool m_test_env_close_request;
	
};

