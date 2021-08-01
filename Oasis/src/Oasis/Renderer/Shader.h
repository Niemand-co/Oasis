#pragma once
#include "Oasis/Core.h"
#include <string>

namespace Oasis {

	class OASIS_API Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& VertexShaderSrc, const std::string& FragmentShaderSrc);
		static Shader* Create(const std::string& filePath);

	};

}