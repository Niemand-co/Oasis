#include "OApch.h"
#include "Shader.h"
#include "Oasis/Log.h"

#include <glad/glad.h>

namespace Oasis {



	Shader::Shader(std::string VertexShaderPath, std::string FragmentShaderPath){

		std::string vShaderSource = VertexShaderPath;
		std::string fShaderSource = FragmentShaderPath;

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
			OASIS_CORE_ASSERT("Link Failed!");
			return;

		}

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

	}

	Shader::~Shader(){

		glDeleteProgram(m_RendererID);

	}

	void Shader::Bind(){

		glUseProgram(m_RendererID);

	}

	void Shader::Unbind(){

		glUseProgram(0);

	}

}