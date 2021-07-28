#include "OApch.h"
#include "Renderer.h"

namespace Oasis {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera){

		m_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();

	}

	void Renderer::EndScene(){
	
	

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray, const std::shared_ptr<Shader> shader){
	
		shader->Bind();
		shader->UploadUniformMat4("viewProjection", m_SceneData->ProjectionViewMatrix);

		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	
	}

}