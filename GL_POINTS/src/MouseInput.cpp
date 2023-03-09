#include "MouseInput.h"

#include "OpenGL/GL_gl.h"
#include "Window.h"


void mouseButtonCallback(GLFWwindow* glfw_window, int button, int action, int mods)
{
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
	window->getMouseInput()->MouseButtonCallback(button, action);
}

void cursorPositionCallback(GLFWwindow* glfw_window, double xpos, double ypos)
{
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
	window->getMouseInput()->CursorPositionCallback(xpos, ypos);
}

MouseInput::MouseInput(Window& window)
:
m_window(window),
m_cursor_pos(0.0f)
{
	// LMB
	m_button_states[1] = false;
	// RMB
	m_button_states[2] = false;

	glfwSetMouseButtonCallback(window.getNative(), mouseButtonCallback);
	glfwSetCursorPosCallback(window.getNative(), cursorPositionCallback);
}

bool MouseInput::isLeftButtonPressed()
{
	return m_button_states[1];
}

bool MouseInput::isRightButtonPressed()
{
	return m_button_states[2];
}

const glm::vec2& MouseInput::getLastCursorPosition() const
{
	return m_cursor_pos;
}

void MouseInput::MouseButtonCallback(const int32_t& button, const int32_t& action)
{
	if (action == GLFW_PRESS) {
		m_button_states[button] = true;
	}
	else if(action == GLFW_RELEASE) {
		m_button_states[button] = false;
	}

}

void MouseInput::CursorPositionCallback(const double& xpos, const double& ypos)
{
	m_cursor_pos.x = static_cast<float>(xpos);
	m_cursor_pos.y = static_cast<float>(ypos);
}
