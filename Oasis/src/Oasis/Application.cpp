#include "OApch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

#include "Oasis/Renderer/Renderer.h"

namespace Oasis {

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		OASIS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float Vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(Vertices, sizeof(Vertices)));

		BufferLayout layout = {

			{ShaderDataType::Float3, "aPos"},
			{ShaderDataType::Float4, "aColor"}

		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		
		uint32_t Indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string VertexShaderSrc = R"(#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Color = aColor;
				v_Position = aPos;
				gl_Position = vec4(aPos, 1.0);
			}
			)";

		std::string FragmentShaderSrc = R"(
			#version 330 core
			out vec4 FragColor;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				FragColor = v_Color;
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
		dispatcher.DispatchEvent<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));

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
			RendererCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
			RendererCommand::Clear();

			Renderer::BeginScene();
			Renderer::EndScene();

			m_Shaders->Bind();
			Renderer::Submit(m_VertexArray);

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

	bool Application::OnKeyPressed(KeyPressedEvent& e) {
		if (e.GetKeyCode() == OASIS_KEY_ESCAPE) {
			OASIS_CORE_TRACE("The Window is Closed!")
			m_Running = false;
			return true;
		}
		return false;
	}

}