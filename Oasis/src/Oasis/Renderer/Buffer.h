#pragma once
#include "Oasis/Core.h"
#include <cstdint>

namespace Oasis {

	class VertexBuffer {

	public:
		
		virtual ~VertexBuffer() {}


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* Vertices, uint32_t size);

	};


	class IndexBuffer {

	public:

		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* Indices, uint32_t size);

	};

}