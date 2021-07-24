#pragma once
#include "Oasis/Renderer/Buffer.h"

namespace Oasis {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:

		OpenGLVertexBuffer(float* Vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

	private:

		uint32_t m_RendererID;

	};

	class OpenGLIndexBuffer : public IndexBuffer {

	public:

		OpenGLIndexBuffer(uint32_t* Vertices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const;

		virtual void Bind() const;
		virtual void Unbind() const;

	private:

		uint32_t m_Count;
		uint32_t m_RendererID;

	};

}