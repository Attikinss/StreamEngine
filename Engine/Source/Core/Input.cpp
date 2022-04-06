#include "Input.h"
#include "Logger.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace SE {
	struct InputInfo {
		std::unordered_map<int, bool> InputMap;
		glm::vec2 LastMousePosition;
		bool CalculateDelta = false;
	};

	static InputInfo s_Info;

	// TODO: Move into a display or panel class to handle screenspace per window/panel/etc
	static glm::vec2 ToScreenSpace(const glm::vec2& mousePosition) {
		// Get window dimensions
		auto [x, y] = Application::Get().GetWindow().GetSize();
		float aspectRatio = x / y;

		// Wacky math time!
		return {
			aspectRatio * (mousePosition.x / (x / 2.0f) - 1.0f),
			-(mousePosition.y / (y / 2.0f) - 1.0f) };
	}

	void Input::Initialize() {
		int32_t keyCount = static_cast<int>(Key::COUNT);
		for (int32_t enumVal = 0; enumVal < keyCount + 1; enumVal++) {
			s_Info.InputMap[enumVal] = false;
		}

		int32_t buttonCount = static_cast<int>(Button::COUNT);
		for (int32_t enumVal = 32; enumVal < keyCount + 1; enumVal++) {
			s_Info.InputMap[enumVal] = false;
		}

		Logger::Trace("Input Initialized...");
	}

	void Input::Update() {
		if (s_Info.CalculateDelta) {
			s_Info.LastMousePosition = GetMousePosition();
			return;
		}
		
		s_Info.CalculateDelta = false;
	}

	bool Input::GetKey(Key key) {
		// Ensure value is not something random and is already in the input map
		int keyValue = static_cast<int>(key);
		if (keyValue < 32 || keyValue > 348) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		int32_t val = glfwGetKey(windowHandle, keyValue);
		return val == GLFW_PRESS;
	}

	bool Input::GetKeyDown(Key key) {
		// Ensure value is not something random and is already in the input map
		int keyValue = static_cast<int>(key);
		if (keyValue < 32 || keyValue > 348) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		bool keyDown = glfwGetKey(windowHandle, keyValue) == GLFW_PRESS;

		// Check if key was already down
		bool keyAlreadyDown = s_Info.InputMap.at(keyValue);
		if (keyDown == keyAlreadyDown) {
			return false;
		}

		// Assign value
		s_Info.InputMap[keyValue] = keyDown;
		return keyDown;
	}

	bool Input::GetKeyUp(Key key) {
		// Ensure value is not something random and is already in the input map
		int keyValue = static_cast<int>(key);
		if (keyValue < 32 || keyValue > 348) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		bool keyUp = glfwGetKey(windowHandle, keyValue) == GLFW_RELEASE;

		// Check if key was already up
		bool keyAlreadyUp = s_Info.InputMap.at(keyValue);
		if (keyUp == keyAlreadyUp) {
			return false;
		}

		// Assign value
		s_Info.InputMap[keyValue] = keyUp;
		return keyUp;
	}

	bool Input::GetMouseButton(Button button) {
		// Ensure value is not something random and is already in the input map
		int buttonValue = static_cast<int>(button);
		if (buttonValue < 0 || buttonValue > 7) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		int32_t val = glfwGetMouseButton(windowHandle, buttonValue);
		return val == GLFW_PRESS;
	}

	bool Input::GetMouseButtonDown(Button button) {
		// Ensure value is not something random and is already in the input map
		int buttonValue = static_cast<int>(button);
		if (buttonValue < 0 || buttonValue > 7) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		bool buttonDown = glfwGetMouseButton(windowHandle, buttonValue) == GLFW_RELEASE;

		// Check if key was already up
		bool buttonAlreadyDown = s_Info.InputMap.at(buttonValue);
		if (buttonDown == buttonAlreadyDown) {
			return false;
		}

		// Assign value
		s_Info.InputMap[buttonValue] = buttonDown;
		return buttonDown;
	}

	bool Input::GetMouseButtonUp(Button button) {
		// Ensure value is not something random and is already in the input map
		int buttonValue = static_cast<int>(button);
		if (buttonValue < 0 || buttonValue > 7) {
			return false;
		}

		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();
		bool buttonUp = glfwGetMouseButton(windowHandle, buttonValue) == GLFW_RELEASE;

		// Check if key was already up
		bool buttonAlreadyUp = s_Info.InputMap.at(buttonValue);
		if (buttonUp == buttonAlreadyUp) {
			return false;
		}

		// Assign value
		s_Info.InputMap[buttonValue] = buttonUp;
		return buttonUp;
	}

	glm::vec2 Input::GetMousePosition(bool screenspace) {
		GLFWwindow* windowHandle = Application::Get().GetWindow().GetHandle();

		// Retrieve mouse position
		double x, y;
		glfwGetCursorPos(windowHandle, &x, &y);
		glm::vec2 mousePosition = { (float)x, (float)y };

		return screenspace ? ToScreenSpace(mousePosition) : mousePosition;
	}

	glm::vec2 Input::GetMouseDelta() {
		s_Info.CalculateDelta = true;
		
		glm::vec2 mousePosition = GetMousePosition();
		glm::vec2 delta = mousePosition - s_Info.LastMousePosition;
		s_Info.LastMousePosition = mousePosition;

		return delta;
	}
}