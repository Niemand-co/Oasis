#include "OApch.h"
#include "OrthographicCamera.h"

namespace Oasis {

	OrthographicCamera::OrthographicCamera(float left, float right, float up, float bottom)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, up)), m_ViewMatrix(glm::mat4(1.0f)), m_Position(glm::vec3(0.0f))
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::ProjectionMatrixUpdate(float left, float right, float up, float bottom){

		m_ProjectionMatrix = glm::ortho(left, right, bottom, up);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void OrthographicCamera::ViewMatrixUpdate() {

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

}
