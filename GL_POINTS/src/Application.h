#pragma once
#include "OpenGL/GL_gl.h"
#include "Window.h"



class Application
{
public:

	Application(const WindowSettings& window_settings);

	void run();

protected:

	virtual void beforeUpdate() = 0;

	virtual void onEvent(const float& delta) = 0;

	virtual void onUpdate(const float& delta) = 0;

	virtual void onImGuiUpdate() {};

private:

	void loop();

	void imGuiInit();
	void imGuiNewFrame();
	void imGuiRender();
	void imGuiShutdown();

protected:
	
	Window m_window;
	KeyboardInput* m_keyboard;
	MouseInput* m_mouse;

};

