#pragma once
#include "Oasis/Core.h"
#include <string>

namespace Oasis {

	class OASIS_API Shader {

	public:

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(std::string& VertexShaderSrc, std::string& FragmentShaderSrc);

	};

}