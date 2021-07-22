#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Oasis {

	class OASIS_API Layer
	{

	public:

		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void ImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline std::string GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;

	};

}