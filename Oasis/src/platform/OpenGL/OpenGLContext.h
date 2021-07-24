#pragma once

#include "Oasis/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Oasis {

	class OpenGLContext : public GraphicsContext{

	public:

		OpenGLContext(GLFWwindow* WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffer() override;

	private:

		GLFWwindow* m_WindowHandle;

	};

}

