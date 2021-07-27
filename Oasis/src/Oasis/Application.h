#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Oasis/Window.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Oasis/Events/KeyEvent.h"
#include "Oasis/Events/MouseEvent.h"

#include "Oasis/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Oasis/Renderer/Shader.h"
#include "Oasis/Renderer/Buffer.h"
#include "Oasis/Renderer/VertexArray.h"

#include "Oasis/KeyCodes.h"

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

		std::shared_ptr<Shader> m_Shaders;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}