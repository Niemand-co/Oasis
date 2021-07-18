#pragma once

#include "Oasis/Layer.h"

#include "Oasis/Events/ApplicationEvent.h"
#include "Oasis/Events/KeyEvent.h"
#include "Oasis/Events/MouseEvent.h"


namespace Oasis {

	class OASIS_API ImGuiLayer : public Layer{

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:

		bool ImGuiMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool ImGuiMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool ImGuiMouseMovedEvent(MouseMoveEvent& e);
		bool ImGuiMouseScrolledEvent(MouseScrollEvent& e);
		bool ImGuiWindowResizedEvent(WindowResizeEvent& e);
		bool ImGuiKeyPressedEvent(KeyPressedEvent& e);
		bool ImGuiKeyReleasedEvent(KeyReleasedEvent& e);
		bool ImGuiKeyTypeEvent(KeyTypeEvent& e);

	private:

		float m_Time = 0.0f;

	};

}

