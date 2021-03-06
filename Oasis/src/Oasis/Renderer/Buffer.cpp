#include "OApch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "platform/OpenGL/OpenGLBuffer.h"

namespace Oasis {

	VertexBuffer* VertexBuffer::Create(float* Vertices, uint32_t size){

		switch (Renderer::GetRendererAPI()) {

		case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
		case RendererAPI::API::OpenGL: {return new OpenGLVertexBuffer(Vertices, size); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;
	
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t size) {
	
		switch (Renderer::GetRendererAPI()) {

		case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
		case RendererAPI::API::OpenGL: {return new OpenGLIndexBuffer(Indices, size); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;
	
	}

}