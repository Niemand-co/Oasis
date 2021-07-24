#include "OApch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Oasis {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* Vertices, uint32_t size) {

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, Vertices, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer(){

		glDeleteBuffers(1, &m_RendererID);

	}

	void OpenGLVertexBuffer::Bind() const {

		glBindBuffer(GL_VERTEX_ARRAY, m_RendererID);

	}

	void OpenGLVertexBuffer::Unbind() const {

		glBindBuffer(GL_VERTEX_ARRAY, 0);

	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* Vertices, uint32_t count) : m_Count(count) {

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), Vertices, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer(){

		glDeleteBuffers(1, &m_RendererID);

	}

	uint32_t OpenGLIndexBuffer::GetCount() const {

		return m_Count;

	}

	void OpenGLIndexBuffer::Bind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	}

	void OpenGLIndexBuffer::Unbind() const {

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

}