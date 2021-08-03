#include "OApch.h"
#include "OrthographicCameraController.h"

#include "Oasis/KeyCodes.h"
#include "Oasis/MouseButtons.h"

#include "Oasis/Input.h"

namespace Oasis {

	OrthographicCameraController::OrthographicCameraController(float AspectRatio, bool rotation) 
		: m_AspectRatio(AspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel), m_Rotation(rotation) {



	}

	void OrthographicCameraController::OnUpdate(float DeltaTime){

		if (Input::IsKeyPressed(OASIS_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * DeltaTime;
		}
		else if (Input::IsKeyPressed(OASIS_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * DeltaTime;
		}
		
		if (Input::IsKeyPressed(OASIS_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * DeltaTime;
		}
		else if (Input::IsKeyPressed(OASIS_KEY_UP)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * DeltaTime;
		}


		if (m_Rotation) {
			if (Input::IsKeyPressed(OASIS_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * DeltaTime;
			else if (Input::IsKeyPressed(OASIS_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * DeltaTime;
			
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

	}

	void OrthographicCameraController::OnEvent(Event& event){

		EventDispatcher dispatcher(event);
		dispatcher.DispatchEvent<MouseScrollEvent>(OASIS_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
		dispatcher.DispatchEvent<WindowResizeEvent>(OASIS_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));

	}

	OrthographicCamera& OrthographicCameraController::GetCamera(){

		return m_Camera;

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrollEvent& e){

		m_ZoomLevel -= e.GetOffsetY() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.ProjectionMatrixUpdate(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
		return false;

	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e){

		m_AspectRatio = (float)e.GetWindowWidth() / (float)e.GetWindowHeight();
		m_Camera.ProjectionMatrixUpdate(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, m_ZoomLevel, -m_ZoomLevel);
		return false;

	}

}