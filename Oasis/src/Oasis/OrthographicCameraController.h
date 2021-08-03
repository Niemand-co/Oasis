#pragma once
#include "Oasis/Renderer/OrthographicCamera.h"

#include "Oasis/Events/MouseEvent.h"
#include "Oasis/Events/ApplicationEvent.h"

#include "Oasis/Core/TimeStep.h"

namespace Oasis {

	class OrthographicCameraController {

	public:

		OrthographicCameraController(float AspectRatio, bool rotation = false);

		void OnUpdate(float DeltaTime);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera();

	private:
		bool OnMouseScrolled(MouseScrollEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:

		float m_AspectRatio;
		bool m_Rotation;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;

	};

}