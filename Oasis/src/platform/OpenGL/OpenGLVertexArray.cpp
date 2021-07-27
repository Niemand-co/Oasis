#include "OApch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Oasis {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {

		switch (type) {

			case ShaderDataType::Float:        return GL_FLOAT;
			case ShaderDataType::Float2:       return GL_FLOAT;
			case ShaderDataType::Float3:       return GL_FLOAT;
			case ShaderDataType::Float4:       return GL_FLOAT;
			case ShaderDataType::Mat3:         return GL_FLOAT;
			case ShaderDataType::Mat4:         return GL_FLOAT;
			case ShaderDataType::Int:          return GL_INT;
			case ShaderDataType::Int2:         return GL_INT;
			case ShaderDataType::Int3:         return GL_INT;
			case ShaderDataType::Int4:         return GL_INT;
			case ShaderDataType::Bool:         return GL_BOOL;

		}

		OASIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return GL_FALSE;

	}

	OpenGLVertexArray::OpenGLVertexArray() {

		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);

	}

	void OpenGLVertexArray::Bind() const {
		
		glBindVertexArray(m_RendererID);

	}

	void OpenGLVertexArray::Unbind() const {

		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer){

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		OASIS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer Without Layout!");

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetElementsCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;

		}

		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer){

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

	}

}