#pragma once
#include "RendererCommand.h"

#include "Shader.h"
#include "OrthographicCamera.h"

namespace Oasis {

	class OASIS_API Renderer {

	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData {

			glm::mat4 ProjectionViewMatrix;

		};
		static SceneData* m_SceneData;

	};

}

