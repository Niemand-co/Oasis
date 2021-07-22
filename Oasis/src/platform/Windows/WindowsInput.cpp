#include "OApch.h"
#include "WindowsInput.h"

#include "Oasis/Application.h"
#include <GLFW/glfw3.h>

namespace Oasis {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImp(int keycode) {

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;

	}

	bool WindowsInput::IsMouseButtonPressedImp(int button)
	{

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMousePosXImp()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return (float)xPos;
	}

	float WindowsInput::GetMousePosYImp()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return (float)yPos;
	}

	std::pair<float, float> WindowsInput::GetMousePosImp()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return std::make_pair((float)xPos, (float)yPos);

		return std::pair<float, float>();
	}

}