#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace Oasis {
	Application::Application(){
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OneEvent, this, std::placeholders::_1));
	}

	void Application::OneEvent(Event& e) {
		OASIS_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

	}

	Application::~Application(){
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}