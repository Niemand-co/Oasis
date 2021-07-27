#include "OApch.h"
#include "Renderer.h"

namespace Oasis {

	void Renderer::BeginScene(){

		

	}

	void Renderer::EndScene(){
	
	

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> vertexArray){
	
		vertexArray->Bind();
		RendererCommand::DrawIndexed(vertexArray);
	
	}

}