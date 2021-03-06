#pragma once
#include <cstdint>
#include "Oasis/Core/Log.h"
#include "Oasis/Core/Core.h"


namespace Oasis {

	enum class ShaderDataType {

		None = 0, Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool

	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {

		switch (type) {

			case ShaderDataType::Float:        return 4;
			case ShaderDataType::Float2:       return 8;
			case ShaderDataType::Float3:       return 12;
			case ShaderDataType::Float4:       return 16;
			case ShaderDataType::Mat3:         return 36;
			case ShaderDataType::Mat4:         return 64;
			case ShaderDataType::Int:          return 4;
			case ShaderDataType::Int2:         return 8;
			case ShaderDataType::Int3:         return 12;
			case ShaderDataType::Int4:         return 16;
			case ShaderDataType::Bool:         return 1;

		}

		OASIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;

	}


	struct BufferElement {

		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {

		}

		uint32_t GetElementsCount() const {
		
			switch (Type) {

				case ShaderDataType::Float:        return 1;
				case ShaderDataType::Float2:       return 2;
				case ShaderDataType::Float3:       return 3;
				case ShaderDataType::Float4:       return 4;
				case ShaderDataType::Mat3:         return 3*3;
				case ShaderDataType::Mat4:         return 4*4;
				case ShaderDataType::Int:          return 1;
				case ShaderDataType::Int2:         return 2;
				case ShaderDataType::Int3:         return 3;
				case ShaderDataType::Int4:         return 4;
				case ShaderDataType::Bool:         return 1;

			}

			OASIS_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;

		}

		uint32_t GetStride() {



		}

	};

	class OASIS_API BufferLayout {

	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {

			CalculateOffsetAndStride();

		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:

		void CalculateOffsetAndStride() {

			uint32_t offset = 0;
			m_Stride = 0;;

			for (auto& element : m_Elements) {

				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;

			}

		}

	private:

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	};


	class OASIS_API VertexBuffer {

	public:
		
		virtual ~VertexBuffer() = default;


		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* Vertices, uint32_t size);

	};


	class OASIS_API IndexBuffer {

	public:

		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* Indices, uint32_t size);

	};

}