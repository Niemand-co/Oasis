#include "OApch.h"
#include "VertexArray.h"

#include "Oasis/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLVertexArray.h"

namespace Oasis {

	VertexArray* VertexArray::Create() {

		switch (Renderer::GetRendererAPI()) {

			case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL: {return new OpenGLVertexArray(); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!")
		return nullptr;

	}

}