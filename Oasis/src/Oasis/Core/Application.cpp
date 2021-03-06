#include "OApch.h"
#include "Application.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Log.h"

#include "Oasis/Renderer/Renderer.h"

namespace Oasis {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		OASIS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		timeStep.reset(TimeStep::Create());
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<WindowCloseEvent>(OASIS_BIND_EVENT_FUNC(Application::OnWindowClose));
		dispatcher.DispatchEvent<WindowResizeEvent>(OASIS_BIND_EVENT_FUNC(Application::OnWindowResize));

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
			
			float DeltaTime = timeStep->UpdateTimeStep();

			if(!m_Minimized){
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timeStep, DeltaTime);
				}
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->ImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		uint32_t width = e.GetWindowWidth(), height = e.GetWindowHeight();
		if (width == 0 || height == 0) {

			m_Minimized = true;
			return false;

		}

		Renderer::ViewportUpdateWithWindow(width, height);

		m_Minimized = false;
		return false;
	}

}