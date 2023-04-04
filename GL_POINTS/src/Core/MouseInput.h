#pragma once
#include <cstdint>
#include <unordered_map>

#include "glm/glm.hpp"

#include "InputCodes.h"

struct GLFWwindow;
class Window;


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);


class MouseInput
{
public:

	MouseInput(Window& window);

	MouseInput(const MouseInput& obj) = delete;
	MouseInput& operator=(const MouseInput& obj) = delete;

	MouseInput(MouseInput&& obj) = delete;
	MouseInput& operator=(MouseInput&& obj) = delete;

	bool isLeftButtonPressed();
	bool isRightButtonPressed();

	const glm::vec2& getLastCursorPosition() const;

	void MouseButtonCallback(const int32_t& button, const int32_t& action);
	void CursorPositionCallback(const double& xpos, const double& ypos);

private:

	Window& m_window;

	std::unordered_map<uint32_t, bool> m_button_states;

	glm::vec2 m_cursor_pos;
};

