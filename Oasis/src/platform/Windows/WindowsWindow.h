#pragma once

#include "Oasis/Window.h"
#include "Oasis/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Oasis {

	class WindowsWindow : public Window{

	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFunc& Callback) override { m_Data.EventCallback = Callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;

		struct WindowData {
			std::string title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFunc EventCallback;
		};

		WindowData m_Data;

	};


}
