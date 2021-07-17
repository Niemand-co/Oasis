#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Oasis/Window.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Oasis/Events/KeyEvent.h"
#include "Oasis/Events/MouseEvent.h"

#include "Oasis/LayerStack.h"

namespace Oasis{
	class OASIS_API Application{

	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;

	};

	Application* CreateApplication();
}