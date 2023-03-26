#pragma once

#include <glm/glm.hpp>


class Camera
{

};

class PerspectiveCamera : public Camera
{
public:

    PerspectiveCamera(const float& window_width, const float& window_height, const glm::vec3& position, const float& fov);

    const glm::mat4& matrix();
    glm::mat4& viewMatrix();
    glm::mat4& perspectiveMatrix();

    glm::vec3& position();
    glm::vec3& front();
    glm::vec3& up();
    float& fov();

    void updatePerspectiveMatrix();
    void updateMatrix();

private:

    glm::mat4 m_perspective_matrix;

    glm::mat4 m_view_matrix;

    glm::mat4 m_combined_matrix;

    glm::vec3 m_position;
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_fov;

    float m_window_width;
    float m_window_height;
};
