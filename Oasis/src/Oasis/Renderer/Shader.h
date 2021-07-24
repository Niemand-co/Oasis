#pragma once
#include <string>

namespace Oasis {

	class Shader {

	public:

		Shader(std::string VertexShaderPath, std::string FragmentShaderPath);
		~Shader();

		void Bind();
		void Unbind();

	private:

		uint32_t m_RendererID;

	};

}