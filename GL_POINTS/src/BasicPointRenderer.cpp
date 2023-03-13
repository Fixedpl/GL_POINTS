#include "BasicPointRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "lasreader_asc.hpp"

#include "OpenGL/GL_Renderer.h"

#include "MouseInput.h"
#include "KeyboardInput.h"



BasicPointRenderer::BasicPointRenderer(WindowSettings window_settings)
	: 
	Application(window_settings),
	m_camera(
		window_settings.width, 
		window_settings.height, 
		m_starting_camera_pos
	)
{
}

void BasicPointRenderer::beforeUpdate()
{
	init();
}

void BasicPointRenderer::onEvent(const float& delta)
{
	handleMouseMovement();

	handleKeyboard(delta);
}

void BasicPointRenderer::onUpdate(const float& dt)
{
	m_shader.setUniformMat4f("u_MVP", m_camera.matrix());
	m_cube_renderer.render();
	m_point_renderer.render();
}

void BasicPointRenderer::init()
{
	m_shader.loadShader("res/shaders/v.glsl", "res/shaders/f.glsl");
	m_shader.bind();

	m_shader.setUniformMat4f("u_MVP", m_camera.matrix());

	m_first_mouse_move = true;

	initTestCube();

	initPoints();

}

void BasicPointRenderer::initPoints()
{
	LASreadOpener* las_read_opener = new LASreadOpener();
	LASreader* las_reader = las_read_opener->open("res/point_clouds/cube.ply");


	while (las_reader->read_point()) {
		LASpoint point = las_reader->point;

		F64 x = las_reader->get_x();
		F64 y = las_reader->get_y();
		F64 z = las_reader->get_z();

		F64 r = point.get_R();
		F64 g = point.get_G();
		F64 b = point.get_B();

		m_point_renderer.addPointAt({ x, y, z }, { r, g, b });
	}

	m_point_renderer.init();
}

void BasicPointRenderer::initTestCube()
{
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  0.0f,  5.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  0.0f, -5.0f));

	m_cube_renderer.addCubeAt(glm::vec3(-5.0f,  0.0f,  0.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 5.0f,  0.0f,  0.0f));

	m_cube_renderer.addCubeAt(glm::vec3( 0.0f, -5.0f, 0.0f));
	m_cube_renderer.addCubeAt(glm::vec3( 0.0f,  5.0f, 0.0f));

	m_cube_renderer.init();
}

void BasicPointRenderer::handleMouseMovement()
{
	glm::vec2 mouse_pos = m_mouse->getLastCursorPosition();
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
	m_camera.front() = glm::normalize(direction);
	m_camera.updateMatrix();
}

void BasicPointRenderer::handleKeyboard(const float& dt)
{
	if (m_keyboard->isKeyPressed(KeyCode::KEY_W)) {
		m_camera.position() += dt * m_movement_speed * m_camera.front();
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_S)) {
		m_camera.position() -= dt * m_movement_speed * m_camera.front();
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_A)) {
		m_camera.position() -= dt * glm::normalize(glm::cross(m_camera.front(), m_camera.up())) * m_movement_speed;
		m_camera.updateMatrix();
	}
	if (m_keyboard->isKeyPressed(KeyCode::KEY_D)) {
		m_camera.position() += dt * glm::normalize(glm::cross(m_camera.front(), m_camera.up())) * m_movement_speed;
		m_camera.updateMatrix();
	}
}
