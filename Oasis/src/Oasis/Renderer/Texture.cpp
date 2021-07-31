#include "OApch.h"
#include "Texture.h"

#include "Oasis/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLTexture.h"

namespace Oasis {

	Ref<Texture2D> Texture2D::Create(const std::string& path) {

		switch (Renderer::GetRendererAPI()) {

			case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL: {return std::make_shared<OpenGLTexture2D>(path); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!")
		return nullptr;

	}

}