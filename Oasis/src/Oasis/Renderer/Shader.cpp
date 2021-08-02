#include "OApch.h"
#include "Shader.h"

#include "Oasis/Renderer/Renderer.h"
#include "platform/OpenGL/OpenGLShader.h"

namespace Oasis {

	Ref<Shader> Shader::Create(const std::string name, const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc){

		switch (Renderer::GetRendererAPI()) {

			case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
			case RendererAPI::API::OpenGL: {return std::make_shared<OpenGLShader>(name, VertexShaderSrc, FragmentShaderSrc); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;

	}

	Ref<Shader> Shader::Create(const std::string& filePath){

		switch (Renderer::GetRendererAPI()) {

		case RendererAPI::API::None: {OASIS_CORE_ASSERT(false, "The Renderer API is not supported!"); return nullptr; }
		case RendererAPI::API::OpenGL: {return std::make_shared<OpenGLShader>(filePath); }

		}

		OASIS_CORE_ASSERT(false, "Unkhown API!");
		return nullptr;
	}

	bool ShaderLibrary::ShaderExist(const std::string& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	void ShaderLibrary::AddShader(const std::string name, const Ref<Shader>& shader){

		OASIS_CORE_ASSERT(!ShaderExist(name), "Shader already exits!");
		m_Shaders[name] = shader;

	}

	void ShaderLibrary::AddShader(const Ref<Shader>& shader){

		auto& name = shader->GetName();
		AddShader(name, shader);

	}

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& filePath){
		
		auto shader = Shader::Create(filePath);
		AddShader(shader);
		
		return shader; 
	}

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& name, const std::string& filePath){

		auto shader = Shader::Create(filePath);
		AddShader(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name){

		OASIS_CORE_ASSERT(ShaderExist(name), "Shader not found!");
		return m_Shaders[name];

	}

}