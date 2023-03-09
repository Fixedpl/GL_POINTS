#include "KeyboardInput.h"

#include "OpenGL/GL_gl.h"
#include "Window.h"

void keyboardCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
    window->getKeyboardInput()->KeyboardCallback(key, action);
}


KeyboardInput::KeyboardInput(Window& window)
:
m_window(window)
{
    glfwSetKeyCallback(m_window.getNative(), keyboardCallback);
}

bool KeyboardInput::isKeyPressed(const KeyCode& key)
{
    return m_key_states[static_cast<uint32_t>(key)];
}

void KeyboardInput::KeyboardCallback(const int32_t& key, const int32_t& action)
{
    if (action == GLFW_PRESS) {
        m_key_states[key] = true;
    }
    else if(action == GLFW_RELEASE) {
        m_key_states[key] = false;
    }

}


