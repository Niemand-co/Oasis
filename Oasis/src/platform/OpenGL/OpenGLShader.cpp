#include "OApch.h"
#include "OpenGLShader.h"
#include "Oasis/Log.h"

#include <fstream>

#include <glad/glad.h>

namespace Oasis {

	GLenum StringToShaderType(std::string type) {

		if (type == "Vertex")
			return GL_VERTEX_SHADER;
		else if (type == "Fragment")
			return GL_FRAGMENT_SHADER;
		else if (type == "Geometry")
			return GL_GEOMETRY_SHADER;

		OASIS_CORE_ASSERT(false, "Unknown Shader Tpye!");
		return 0;

	}

	int OpenGLShader::GetLocation(uint32_t program, std::string name) {

		if (recorded_location.find(name) != recorded_location.end())
			return recorded_location[name];
		int location = glGetUniformLocation(program, name.c_str());
		recorded_location[name] = location;
		return location;

	}

	std::string OpenGLShader::ReadFile(std::string filePath)
	{
		std::string shaderSrc;
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in) {

			in.seekg(0, std::ios::end);
			shaderSrc.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&shaderSrc[0], shaderSrc.size());
			in.close();

		}
		else {

			OASIS_CORE_ASSERT(false, "Unable to Read Shaders !");

		}

		return shaderSrc;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ShaderPreprocess(const std::string& ShaderSrc){

		std::unordered_map<GLenum, std::string> Shaders;

		const char* TypeToken = "#type";
		size_t TypeTokenLength = std::strlen(TypeToken);
		size_t pos = ShaderSrc.find(TypeToken, 0);

		while (pos != std::string::npos) {

			size_t eol = ShaderSrc.find_first_of("\r\n", pos);
			OASIS_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + TypeTokenLength + 1;
			std::string type = ShaderSrc.substr(begin, eol - begin);
			
			size_t nextlinePos = ShaderSrc.find_first_of("\r\n", eol);
			pos = ShaderSrc.find(TypeToken, nextlinePos);

			Shaders[StringToShaderType(type)] = ShaderSrc.substr(nextlinePos, pos - (nextlinePos == std::string::npos ? ShaderSrc.size() - 1 : nextlinePos));

		}

		return Shaders;

	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& Shaders){

		m_RendererID = glCreateProgram();

		std::vector<GLuint> glShaders(Shaders.size());

		for (auto key : Shaders) {

			GLenum shaderType = key.first;
			const std::string source = key.second;

			GLuint shader = glCreateShader(shaderType);
			const GLchar* shaderSource = (const GLchar*)source.c_str();

			glShaderSource(shader, 1, &shaderSource, 0);
			glCompileShader(shader);

			GLint IsCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &IsCompiled);
			if (IsCompiled == GL_FALSE) {

				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				OASIS_CORE_ERROR("Shader Compilation Error: {0}", infoLog.data());
				OASIS_CORE_ASSERT(false, "Compilation Failed!");
				return;
			}

			glAttachShader(m_RendererID, shader);
			glShaders.push_back(shader);

		}

		glLinkProgram(m_RendererID);
		GLint IsLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &IsLinked);
		if (IsLinked == GL_FALSE) {

			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			for (auto s : glShaders) {
				glDeleteShader(s);
			}

			OASIS_CORE_ERROR("Shader Program Link Error: {0}", infoLog.data());
			OASIS_CORE_ASSERT(false, "Link Failed!");
			return;

		}

		for (auto s : glShaders) {
			glDeleteShader(s);
		}

	}

	OpenGLShader::OpenGLShader(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc) {

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = VertexShaderSrc;
		sources[GL_FRAGMENT_SHADER] = FragmentShaderSrc;
		Compile(sources);

	}

	OpenGLShader::OpenGLShader(const std::string& filePath){

		std::string ShaderSrc = ReadFile(filePath);
		auto Shaders = ShaderPreprocess(ShaderSrc);
		Compile(Shaders);

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