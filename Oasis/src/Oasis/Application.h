#pragma once

#include "OApch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Oasis/Window.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Oasis/Events/KeyEvent.h"
#include "Oasis/Events/MouseEvent.h"

#include "Oasis/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Oasis{
	class OASIS_API Application{

	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}