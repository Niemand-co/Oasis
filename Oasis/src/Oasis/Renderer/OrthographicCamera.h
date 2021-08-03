#pragma once
#include "Oasis/Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {

	class OASIS_API OrthographicCamera {

	public:

		OrthographicCamera(float left, float right, float up, float bottom);
		void ProjectionMatrixUpdate(float left, float right, float up, float bottom);

		const glm::vec3 GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; ViewMatrixUpdate(); }

		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; ViewMatrixUpdate(); }

		const glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4 GetProjectionViewMatrix() { return m_ProjectionViewMatrix; }

	private:

		void ViewMatrixUpdate();

	private:

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;

	};

}