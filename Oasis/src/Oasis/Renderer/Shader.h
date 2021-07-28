#pragma once
#include "Oasis/Core.h"
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Oasis {

	class OASIS_API Shader {

	public:

		Shader(std::string VertexShaderPath, std::string FragmentShaderPath);
		~Shader();

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string, glm::mat4 matrix);

	private:

		uint32_t m_RendererID;

	};

}