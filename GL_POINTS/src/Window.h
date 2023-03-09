#pragma once
#include <iostream>
#include <array>
#include <queue>

#include <glm/glm.hpp>


struct GLFWwindow;
class KeyboardInput;
class MouseInput;

struct WindowSettings
{
	WindowSettings(
		const uint32_t& _width = 1280, 
		const uint32_t& _height = 720, 
		const std::string& _title = "Window", 
		const bool& _v_sync = true,
		const bool& _opengl_debug = true,
		const uint32_t& _opengl_major_version = 4,
		const uint32_t& _opengl_minor_version = 5
	);

	uint32_t width;
	uint32_t height;

	std::string title;

	bool v_sync;

	bool opengl_debug;
	uint32_t opengl_major_version;
	uint32_t opengl_minor_version;
};


class Window
{
public:

	Window(const WindowSettings& window_settings);
	~Window();

	void create();

	WindowSettings getWindowSettings() const;

	void setVSync(const bool& value);

	bool isRunning() const;

	void swapBuffers();

	void shutdown();

	GLFWwindow* getNative();
	
	KeyboardInput* getKeyboardInput();
	MouseInput* getMouseInput();

private:

	void enableOpenGLDebugging();

	void setOpenGLVersion(const uint32_t& major, const uint32_t& minor);

private:
	
	GLFWwindow* m_window;
	WindowSettings m_window_settings;

	KeyboardInput* m_keyboard_input;
	MouseInput* m_mouse_input;
};

