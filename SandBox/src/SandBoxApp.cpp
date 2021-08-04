#include <Oasis.h>
#include "platform/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include <memory>

#include "SandBox2D.h"

class ExampleLayer : public Oasis::Layer {

public:

	std::string VertexShaderSrc = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			out vec4 color;
			
			uniform mat4 model;
			uniform mat4 viewProjection;

			void main(){
				color = aColor;
				gl_Position = viewProjection * model * vec4(aPos, 1.0);
			}
			)";

	std::string FragmentShaderSrc = R"(
			#version 330 core
			out vec4 FragColor;
			in vec4 color;

			void main(){
				FragColor = color;
			}

			)";
	
	ExampleLayer() : Layer("Example"), m_CameraController(16.0f / 9.0f, true){
	
		// ---Triangle-----------------------------
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

		// -----------------------------------


		// ---Square-----------------------------
		m_SquareVertexArray.reset(Oasis::VertexArray::Create());
		float SquareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};
		m_SquareVertexBuffer.reset(Oasis::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));


		Oasis::BufferLayout SquareLayout = {

			{Oasis::ShaderDataType::Float3, "aPos"},
			{Oasis::ShaderDataType::Float2, "aTexCoord"}

		};

		m_SquareVertexBuffer->SetLayout(SquareLayout);
		m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);

		uint32_t SquareIndices[6] = { 0, 1, 3, 1, 2, 3 };
		m_SquareIndexBuffer.reset(Oasis::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));

		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		// -----------------------------------
		auto SquareShader = m_Shaders.LoadShader("assets/shaders/SquareShader.glsl");
		m_Shader = Oasis::Shader::Create("normalShader", VertexShaderSrc, FragmentShaderSrc);

		m_Texture = Oasis::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Oasis::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Oasis::OpenGLShader>(SquareShader)->Bind();
		std::dynamic_pointer_cast<Oasis::OpenGLShader>(SquareShader)->UploadUniformInt("tex", 0);

	}
	
	void OnUpdate(std::shared_ptr<Oasis::TimeStep> timeStep, float DeltaTime) override {

		m_CameraController.OnUpdate(DeltaTime);

		if (Oasis::Input::IsKeyPressed(OASIS_KEY_A)) {
			m_Position.x -= m_StuffTranslationSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_D)) {
			m_Position.x += m_StuffTranslationSpeed * DeltaTime;
		}
		
		if (Oasis::Input::IsKeyPressed(OASIS_KEY_W)) {
			m_Position.y += m_StuffTranslationSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_S)) {
			m_Position.y -= m_StuffTranslationSpeed * DeltaTime;
		}

		Oasis::RendererCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
		Oasis::RendererCommand::Clear();

		Oasis::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		auto SquareShader = m_Shaders.GetShader("SquareShader");

		std::dynamic_pointer_cast<Oasis::OpenGLShader>(SquareShader)->Bind();
		std::dynamic_pointer_cast<Oasis::OpenGLShader>(SquareShader)->UploadUniformFloat3("u_Color", SquareColor);

		m_Texture->Bind();
		Oasis::Renderer::Submit(m_SquareVertexArray, SquareShader, glm::mat4(1.0f));
		m_LogoTexture->Bind();
		Oasis::Renderer::Submit(m_SquareVertexArray, SquareShader, transform);

		//Oasis::Renderer::Submit(m_VertexArray, m_Shader, glm::mat4(1.0f));

		Oasis::Renderer::EndScene();

	}

	virtual void ImGuiRender() override {

		ImGui::Begin("Editor");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(SquareColor));
		ImGui::End();

	}

	void OnEvent(Oasis::Event& e) override {

		m_CameraController.OnEvent(e);

	}

	bool OnKeyPressed(Oasis::KeyPressedEvent& e) {
		/*if (e.GetKeyCode() == OASIS_KEY_LEFT) {
			
			m_CameraPosition.x -= m_CameraSpeed;

		}*/
		return false;
	}

private:

	Oasis::ShaderLibrary m_Shaders;
	Oasis::Ref<Oasis::Shader> m_Shader;
	Oasis::Ref<Oasis::VertexBuffer> m_VertexBuffer;
	Oasis::Ref<Oasis::IndexBuffer> m_IndexBuffer;
	Oasis::Ref<Oasis::VertexArray> m_VertexArray;

	Oasis::Ref<Oasis::VertexBuffer> m_SquareVertexBuffer;
	Oasis::Ref<Oasis::IndexBuffer> m_SquareIndexBuffer;
	Oasis::Ref<Oasis::VertexArray> m_SquareVertexArray;

	Oasis::Ref<Oasis::Texture2D> m_Texture;
	Oasis::Ref<Oasis::Texture2D> m_LogoTexture;

	glm::vec3 SquareColor = { 0.2f, 0.3f, 0.8f };

	Oasis::OrthographicCameraController m_CameraController;

	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	float m_StuffTranslationSpeed = 1.0f;
	
};


class SandBox : public Oasis::Application {

public:
	SandBox(){
		//PushLayer(new ExampleLayer());
		PushLayer(new SandBox2D());
	}

	~SandBox() {

	}

};

Oasis::Application* Oasis::CreateApplication() {
	return new SandBox();
}