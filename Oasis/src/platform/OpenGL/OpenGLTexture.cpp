#include "OApch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Oasis {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path){

		int width, height, nrChannels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		OASIS_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (nrChannels == 1) {
			internalFormat = GL_RED;
			dataFormat = GL_RED;
		}
		else if (nrChannels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (nrChannels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}

		OASIS_CORE_ASSERT(internalFormat & dataFormat, "Unsupported Format!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D(){

		glDeleteTextures(1, &m_RendererID);

	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {

		glBindTextureUnit(slot, m_RendererID);

	}

}