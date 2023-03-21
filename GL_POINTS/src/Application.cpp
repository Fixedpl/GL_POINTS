#include "Application.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <implot/implot.h>

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

	imGuiInit();
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

		imGuiNewFrame();
		
		float new_time = static_cast<float>(glfwGetTime());
		float frame_time = new_time - current_time;
		current_time = new_time;

		onEvent(frame_time);
		onUpdate(frame_time);

		onImGuiUpdate();

		imGuiRender();

		m_window.swapBuffers();
	}

	m_window.shutdown();
}

void Application::imGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window.getNative(), true);
	const WindowSettings& window_settings = m_window.getWindowSettings();
	std::string glsl_version =
		"#version " +
		std::to_string(window_settings.opengl_major_version) +
		std::to_string(window_settings.opengl_minor_version) +
		"0";
	ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void Application::imGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Application::imGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::imGuiShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}
