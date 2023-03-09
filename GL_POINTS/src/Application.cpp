#include "Application.h"


#include "OpenGL/GL_Renderer.h"
#include "OpenGL/GL_Context.h"

#include "KeyboardInput.h"
#include "MouseInput.h"



Application::Application(const WindowSettings& window_settings)
:
m_window(window_settings)
{
	m_window.create();

	OpenGL::Context::create();
	OpenGL::Renderer::init();
	OpenGL::Renderer::setClearColor(glm::vec4(0.5f, 0.65f, 1.0f, 1.0f));

	m_keyboard = m_window.getKeyboardInput();
	m_mouse = m_window.getMouseInput();

}

void Application::run()
{
	loop();
}

void Application::loop()
{
	beforeUpdate();

	float current_time = static_cast<float>(glfwGetTime());

	while (m_window.isRunning())
	{
		OpenGL::Renderer::clear();

		
		float new_time = static_cast<float>(glfwGetTime());
		float frame_time = new_time - current_time;
		current_time = new_time;

		onEvent(frame_time);
		onUpdate(frame_time);

		m_window.swapBuffers();
	}

	m_window.shutdown();
}
