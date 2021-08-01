#include "OApch.h"
#include "Shader.h"

#include "Oasis/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Oasis {

	Shader* Shader::Create(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc) {

		switch (Renderer::GetRendererAPI()) {

			case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL: {return new OpenGLShader(VertexShaderSrc, FragmentShaderSrc); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;

	}

	Shader* Shader::Create(const std::string& filePath){

		switch (Renderer::GetRendererAPI()) {

		case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
		case RendererAPI::API::OpenGL: {return new OpenGLShader(filePath); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;
	}

}