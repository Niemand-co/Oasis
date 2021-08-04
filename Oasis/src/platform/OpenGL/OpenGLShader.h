#pragma once
#include "Oasis/Renderer/Shader.h"

#include "Oasis/Core/Core.h"
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef unsigned int GLenum;


namespace Oasis {

	class OASIS_API OpenGLShader : public Shader{

	public:

		OpenGLShader(const std::string name, const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
		OpenGLShader(const std::string& filePath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string&, int value);

		void UploadUniformFloat(const std::string&, float& value);
		void UploadUniformFloat2(const std::string&, const glm::vec2& value);
		void UploadUniformFloat3(const std::string&, const glm::vec3& value);
		void UploadUniformFloat4(const std::string&, const glm::vec4& value);
		
		void UploadUniformMat3(const std::string&, const glm::mat3& value);
		void UploadUniformMat4(const std::string&, const glm::mat4& value);

		int GetLocation(uint32_t program, std::string name);

	private:

		std::string ReadFile(std::string);
		std::unordered_map<GLenum, std::string> ShaderPreprocess(const std::string& ShaderSrc);
		void Compile(const std::unordered_map<GLenum, std::string>&);

	private:

		uint32_t m_RendererID;
		std::string m_Name;
		std::unordered_map<std::string, int> recorded_location;

	};

}