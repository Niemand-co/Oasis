#include "OApch.h"
#include "OpenGLShader.h"
#include "Oasis/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Oasis {

	int OpenGLShader::GetLocation(uint32_t program, std::string name) {

		if (recorded_location.find(name) != recorded_location.end())
			return recorded_location[name];
		int location = glGetUniformLocation(program, name.c_str());
		recorded_location[name] = location;
		return location;

	}

	OpenGLShader::OpenGLShader(std::string& VertexShaderSrc, std::string& FragmentShaderSrc) {

		std::string vShaderSource = VertexShaderSrc;
		std::string fShaderSource = FragmentShaderSrc;

		GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* vSource = (const GLchar*)vShaderSource.c_str();
		const GLchar* fSource = (const GLchar*)fShaderSource.c_str();

		glShaderSource(VertexShader, 1, &vSource, 0);
		glShaderSource(FragmentShader, 1, &fSource, 0);

		glCompileShader(VertexShader);
		glCompileShader(FragmentShader);

		GLint IsCompiled = 0;
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &IsCompiled);
		if (IsCompiled == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(VertexShader);

			OASIS_CORE_ERROR("VertexShader Compilation Error: {0}", infoLog.data());
			OASIS_CORE_ASSERT(false, "Compilation Failed!");
			return;
		}

		IsCompiled = 0;
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &IsCompiled);
		if (IsCompiled == GL_FALSE) {

			GLint maxLength = 0;
			glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(FragmentShader);

			OASIS_CORE_ERROR("FragmentShader Compilation Error: {0}", infoLog.data());
			OASIS_CORE_ASSERT(false, "Compilation Failed!");
			return;
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, VertexShader);
		glAttachShader(m_RendererID, FragmentShader);

		glLinkProgram(m_RendererID);
		GLint IsLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &IsLinked);
		if (IsLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			OASIS_CORE_ERROR("Shader Program Link Error: {0}", infoLog.data());
			OASIS_CORE_ASSERT(false, "Link Failed!");
			return;

		}

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

	}

	OpenGLShader::~OpenGLShader() {

		glDeleteProgram(m_RendererID);

	}

	void OpenGLShader::Bind() const {

		glUseProgram(m_RendererID);

	}

	void OpenGLShader::Unbind() const {

		glUseProgram(0);

	}

	void OpenGLShader::UploadUniformInt(const std::string& paraName, int value)
	{
		glUniform1i(GetLocation(m_RendererID, paraName), value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& paraName, float& value)
	{
		glUniform1f(GetLocation(m_RendererID, paraName), value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& paraName, const glm::vec2& value)
	{
		glUniform2f(GetLocation(m_RendererID, paraName), value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& paraName, const glm::vec3& value)
	{
		glUniform3f(GetLocation(m_RendererID, paraName), value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& paraName, const glm::vec4& value)
	{
		glUniform4f(GetLocation(m_RendererID, paraName), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& paraName, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetLocation(m_RendererID, paraName), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& paraName, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetLocation(m_RendererID, paraName), 1, GL_FALSE, glm::value_ptr(value));
	}

}