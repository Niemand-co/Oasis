#pragma once

#include <memory>
#include "Oasis/Renderer/Buffer.h"

namespace Oasis {

	class VertexArray {

	public:

		virtual ~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create();

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

	};

}