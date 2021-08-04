#include "OApch.h"
#include "OpenGLContext.h"
#include "Oasis/Core/Core.h"
#include "Oasis/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Oasis {

	OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle) : m_WindowHandle(WindowHandle) {
	
		OASIS_ASSERT(WindowHandle, "Handle is null!");

	}

	void OpenGLContext::Init() {

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OASIS_CORE_ASSERT(status, "Failed to initialize Glad!");

		OASIS_CORE_INFO("OpenGL :");
		OASIS_CORE_INFO("OpenGL Vendor : {0}", glGetString(GL_VENDOR));
		OASIS_CORE_INFO("OpenGL Renderer : {0}", glGetString(GL_RENDERER));
		OASIS_CORE_INFO("OpenGL Version : {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffer() {

		glfwSwapBuffers(m_WindowHandle);

	}

}