#pragma once
#include "Oasis/Renderer/Shader.h"

#include "Oasis/Core.h"
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Oasis {

	class OASIS_API OpenGLShader : public Shader{

	public:

		OpenGLShader(std::string& VertexShaderPath, std::string& FragmentShaderPath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string&, int& value);

		void UploadUniformFloat(const std::string&, float& value);
		void UploadUniformFloat2(const std::string&, const glm::vec2& value);
		void UploadUniformFloat3(const std::string&, const glm::vec3& value);
		void UploadUniformFloat4(const std::string&, const glm::vec4& value);
		
		void UploadUniformMat3(const std::string&, const glm::mat3& value);
		void UploadUniformMat4(const std::string&, const glm::mat4& value);

		int GetLocation(uint32_t program, std::string name);

	private:

		uint32_t m_RendererID;
		std::unordered_map<std::string, int> recorded_location;

	};

}