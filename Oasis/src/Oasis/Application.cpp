#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Oasis {

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		OASIS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {
		OASIS_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {

			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;

		}

	}

	Application::~Application(){
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}