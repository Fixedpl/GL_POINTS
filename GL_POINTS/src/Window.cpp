#include "Window.h"

#include "GLFW/glfw3.h"

#include "KeyboardInput.h"
#include "MouseInput.h"


WindowSettings::WindowSettings(
	const uint32_t& _width,
	const uint32_t& _height,
	const std::string& _title,
	const bool& _v_sync,
	const bool& _opengl_debug,
	const uint32_t& _opengl_major_version,
	const uint32_t& _opengl_minor_version)
:
width(_width),
height(_height),
title(_title),
v_sync(_v_sync),
opengl_debug(_opengl_debug),
opengl_major_version(_opengl_major_version),
opengl_minor_version(_opengl_minor_version)
{
}

WindowSettings Window::getWindowSettings() const
{
	return m_window_settings;
}

Window::Window(const WindowSettings& window_settings)
: 
m_window_settings(window_settings),
m_keyboard_input(nullptr),
m_mouse_input(nullptr)
{
}

Window::~Window()
{
	delete m_keyboard_input;
	delete m_mouse_input;
}


void glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}


void Window::create()
{
	glfwSetErrorCallback(glfwError);
	if (!glfwInit()) {
		std::cout << "ERROR: Couldn't initialize GLFW." << std::endl;
	}

	if (m_window_settings.opengl_debug) {
		enableOpenGLDebugging();
	}

	setOpenGLVersion(m_window_settings.opengl_major_version, m_window_settings.opengl_minor_version);

	m_window = glfwCreateWindow(m_window_settings.width, m_window_settings.height, m_window_settings.title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		std::cout << "ERROR: Couldn't create window." << std::endl;
	}

	glfwMakeContextCurrent(m_window);
	setVSync(m_window_settings.v_sync);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(m_window, this);

	m_keyboard_input = new KeyboardInput(*this);
	m_mouse_input = new MouseInput(*this);
}


void Window::setVSync(const bool& value)
{
	m_window_settings.v_sync = value;
	if (m_window_settings.v_sync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

bool Window::isRunning() const
{
	return !glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Window::shutdown()
{
	glfwTerminate();
}

GLFWwindow* Window::getNative()
{
	return m_window;
}

void Window::enableOpenGLDebugging()
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
}

void Window::setOpenGLVersion(const uint32_t& major, const uint32_t& minor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

KeyboardInput* Window::getKeyboardInput()
{
	return m_keyboard_input;
}

MouseInput* Window::getMouseInput()
{
	return m_mouse_input;
}



