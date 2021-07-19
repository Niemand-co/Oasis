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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void ImGuiRender() override;

		void Begin();
		void End();

	private:

		float m_Time = 0.0f;

	};

}

