#include "OApch.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Oasis {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init() {

		RendererCommand::Init();

	}

	void Renderer::BeginScene(OrthographicCamera& camera){

		m_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();

	}

	void Renderer::EndScene(){
	
	

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform){
	
		std::dynamic_pointer_cast<OpenGLShader>(shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("viewProjection", m_SceneData->ProjectionViewMatrix); 
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("model", transform);
		
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	
		shader->Unbind();
		vertexArray->Unbind();

	}

}