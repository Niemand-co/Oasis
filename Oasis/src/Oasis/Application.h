#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Oasis/Window.h"

namespace Oasis{
	class OASIS_API Application{

	public:
		Application();
		virtual ~Application();
		void Run();

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	Application* CreateApplication();
}