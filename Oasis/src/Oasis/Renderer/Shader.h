#pragma once
#include "Oasis/Core/Core.h"
#include <string>

namespace Oasis {

	class OASIS_API Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string name, const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc);
		static Ref<Shader> Create(const std::string& filePath);

	};

	class ShaderLibrary {

	public:

		bool ShaderExist(const std::string& name);

		void AddShader(const std::string name, const Ref<Shader>& shader);
		void AddShader(const Ref<Shader>& shader);
		Ref<Shader> LoadShader(const std::string& filePath);
		Ref<Shader> LoadShader(const std::string& name, const std::string& filePath);

		Ref<Shader> GetShader(const std::string& name);

	private:

		std::unordered_map<std::string, Ref<Shader>> m_Shaders;

	};

}