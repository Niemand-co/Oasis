#include <Oasis.h>
#include "platform/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include <memory>

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

	std::string CubeVertexShaderSrc = R"(#version 330 core
			layout (location = 0) in vec3 aPos;

			uniform mat4 viewProjection;
			uniform mat4 model;

			void main(){

				gl_Position = viewProjection * model * vec4(aPos, 1.0);
			}
			)";

	std::string CubeFragmentShaderSrc = R"(
			#version 330 core
			out vec4 FragColor;
			uniform vec3 u_Color;

			void main(){
				FragColor = vec4(u_Color, 1.0);
				//FragColor = vec4(0.2, 0.3, 0.8, 1.0);
			}

			)";
	
	ExampleLayer() : Layer("Example"), camera(-1.6f, 1.6f, 0.9f, -0.9f), m_CameraPosition(glm::vec3(0.0f)), m_CameraRotation(0.0f), m_Position(glm::vec3(0.0f)){
	
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


		// ---Cube-----------------------------
		m_CubeVertexArray.reset(Oasis::VertexArray::Create());
		float CubeVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		m_CubeVertexBuffer.reset(Oasis::VertexBuffer::Create(CubeVertices, sizeof(CubeVertices)));


		Oasis::BufferLayout CubeLayout = {

			{Oasis::ShaderDataType::Float3, "aPos"}

		};

		m_CubeVertexBuffer->SetLayout(CubeLayout);
		m_CubeVertexArray->AddVertexBuffer(m_CubeVertexBuffer);

		uint32_t CubeIndices[6] = { 0, 1, 3, 1, 2, 3 };
		m_CubeIndexBuffer.reset(Oasis::IndexBuffer::Create(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t)));

		m_CubeVertexArray->SetIndexBuffer(m_CubeIndexBuffer);

		// -----------------------------------
		m_CubeShaders.reset(Oasis::Shader::Create(CubeVertexShaderSrc, CubeFragmentShaderSrc));
		m_Shaders.reset(Oasis::Shader::Create(VertexShaderSrc, FragmentShaderSrc));

	}
	
	void OnUpdate(std::shared_ptr<Oasis::TimeStep> timeStep, float DeltaTime) override {

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

		if (Oasis::Input::IsKeyPressed(OASIS_KEY_W)) {
			m_Position.y += m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_A)) {
			m_Position.x -= m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_S)) {
			m_Position.y -= m_CameraSpeed * DeltaTime;
		}
		else if (Oasis::Input::IsKeyPressed(OASIS_KEY_D)) {
			m_Position.x += m_CameraSpeed * DeltaTime;
		}

		Oasis::RendererCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
		Oasis::RendererCommand::Clear();

		Oasis::Renderer::BeginScene(camera);

		camera.SetPosition(m_CameraPosition);
		camera.SetRotation(m_CameraRotation);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		std::dynamic_pointer_cast<Oasis::OpenGLShader>(m_CubeShaders)->Bind();
		std::dynamic_pointer_cast<Oasis::OpenGLShader>(m_CubeShaders)->UploadUniformFloat3("u_Color", SquareColor);
		Oasis::Renderer::Submit(m_CubeVertexArray, m_CubeShaders, transform);

		Oasis::Renderer::Submit(m_VertexArray, m_Shaders, glm::mat4(1.0f));

		Oasis::Renderer::EndScene();

	}

	virtual void ImGuiRender() override {

		ImGui::Begin("Editor");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(SquareColor));
		ImGui::End();

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

	std::shared_ptr<Oasis::Shader> m_CubeShaders;
	std::shared_ptr<Oasis::VertexBuffer> m_CubeVertexBuffer;
	std::shared_ptr<Oasis::IndexBuffer> m_CubeIndexBuffer;
	std::shared_ptr<Oasis::VertexArray> m_CubeVertexArray;

	glm::vec3 SquareColor = { 0.2f, 0.3f, 0.8f };

	Oasis::OrthographicCamera camera;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_Position;
	float m_CameraRotation;
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