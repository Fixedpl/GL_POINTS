#pragma once
#include <unordered_map>

#include "InputCodes.h"

struct GLFWwindow;
class Window;

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);


class KeyboardInput
{
public:

	KeyboardInput(Window& window);

	KeyboardInput(const KeyboardInput& obj) = delete;
	KeyboardInput& operator=(const KeyboardInput& obj) = delete;

	KeyboardInput(KeyboardInput&& obj) = delete;
	KeyboardInput& operator=(KeyboardInput&& obj) = delete;

	bool isKeyPressed(const KeyCode& key);


	void KeyboardCallback(const int32_t& key, const int32_t& action);
	
private:

	Window& m_window;

	std::unordered_map<uint32_t, bool> m_key_states;
};
