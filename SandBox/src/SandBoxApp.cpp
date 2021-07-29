#include <Oasis.h>
#include "imgui.h"

class ExampleLayer : public Oasis::Layer {

public:
	
	ExampleLayer() : Layer("Example"), camera(-1.6f, 1.6f, 0.9f, -0.9f), m_CameraPosition(glm::vec3(0.0f, 0.0f, 0.0f)){
	
		m_VertexArray.reset(Oasis::VertexArray::Create());

		float Vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(Oasis::VertexBuffer::Create(Vertices, sizeof(Vertices)));

		Oasis::BufferLayout layout = {

			{Oasis::ShaderDataType::Float3, "aPos"},
			{Oasis::ShaderDataType::Float4, "aColor"}

		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t Indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(Oasis::IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string VertexShaderSrc = R"(#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 viewProjection;

			void main(){
				v_Color = aColor;
				v_Position = aPos;
				gl_Position = viewProjection * vec4(aPos, 1.0);
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


		m_Shaders.reset(new Oasis::Shader(VertexShaderSrc, FragmentShaderSrc));

	}
	
	void OnUpdate(std::shared_ptr<Oasis::TimeStep> timeStep, float DeltaTime) override {

		OASIS_TRACE("Time: {0}s", timeStep->GetSeconds());

		if (Oasis::Input::IsKeyPressed(OASIS_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_UP)) {
			m_CameraPosition.y += m_CameraSpeed * DeltaTime;
		}

		Oasis::RendererCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
		Oasis::RendererCommand::Clear();

		Oasis::Renderer::BeginScene(camera);

		camera.SetPosition(m_CameraPosition);
		Oasis::Renderer::Submit(m_VertexArray, m_Shaders);

		Oasis::Renderer::EndScene();


	}

	virtual void ImGuiRender() override {
	}

	void OnEvent(Oasis::Event& e) override {

		Oasis::EventDispatcher dispatcher(e);
		dispatcher.DispatchEvent<Oasis::KeyPressedEvent>(std::bind(&ExampleLayer::OnKeyPressed, this, std::placeholders::_1));

	}

	bool OnKeyPressed(Oasis::KeyPressedEvent& e) {
		/*if (e.GetKeyCode() == OASIS_KEY_LEFT) {
			
			m_CameraPosition.x -= m_CameraSpeed;

		}*/
		return false;
	}

private:

	std::shared_ptr<Oasis::Shader> m_Shaders;
	std::shared_ptr<Oasis::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Oasis::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Oasis::VertexArray> m_VertexArray;
	Oasis::OrthographicCamera camera;

	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;
};


class SandBox : public Oasis::Application {

public:
	SandBox(){
		PushLayer(new ExampleLayer());
	}

	~SandBox() {

	}

};

Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}