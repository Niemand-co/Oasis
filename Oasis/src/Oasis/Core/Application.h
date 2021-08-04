#pragma once

#include "Core.h"
#include "Oasis/Events/Event.h"
#include "Oasis/Core/Window.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Oasis/Events/KeyEvent.h"
#include "Oasis/Events/MouseEvent.h"

#include "Oasis/Core/LayerStack.h"
#include "Oasis/ImGui/ImGuiLayer.h"

#include "Oasis/Renderer/Shader.h"
#include "Oasis/Renderer/Buffer.h"
#include "Oasis/Renderer/VertexArray.h"
#include "Oasis/Renderer/OrthographicCamera.h"
#include "Oasis/Core/TimeStep.h"
#include "platform/OpenGL/OpenGLTimeStep.h"


#include "Oasis/Core/KeyCodes.h"

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

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true, m_Minimized = false;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		LayerStack m_LayerStack;

		Ref<TimeStep> timeStep;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}