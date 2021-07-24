#include "OApch.h"
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

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float Vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t Indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

		std::string VertexShaderSrc = R"(#version 330 core
			layout (location = 0) in vec3 aPos;

			void main(){
				gl_Position = vec4(aPos, 1.0);
			}
			)";

		std::string FragmentShaderSrc = R"(
			#version 330 core
			out vec4 FragColor;
	

			void main(){
				FragColor = vec4(0.8, 0.2, 0.3, 1.0);
			}

			)";


		m_Shaders.reset(new Shader(VertexShaderSrc, FragmentShaderSrc));

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e) {

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
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shaders->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
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

}