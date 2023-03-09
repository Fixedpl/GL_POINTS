#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(const float& window_width, const float& window_height, const glm::vec3& position)
{
    m_perspective_matrix = glm::perspective(glm::radians(60.0f), window_width / window_height, 0.1f, 100.0f);
    m_position = position;
    updateMatrix();
}

const glm::mat4 &PerspectiveCamera::matrix()
{
    return m_combined_matrix;
}

glm::mat4 &PerspectiveCamera::viewMatrix()
{
    return m_view_matrix;
}

glm::mat4 &PerspectiveCamera::perspectiveMatrix()
{
    return m_perspective_matrix;
}

glm::vec3 &PerspectiveCamera::position()
{
    return m_position;
}

glm::vec3 &PerspectiveCamera::front()
{
    return m_front;
}

glm::vec3 &PerspectiveCamera::up()
{
    return m_up;
}

void PerspectiveCamera::updateMatrix()
{
    m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
    m_combined_matrix = m_perspective_matrix * m_view_matrix;
}
