#pragma once

#include "Oasis/Core.h"
#include "Oasis/Events/Event.h"

namespace Oasis {
	struct WindowProps {

		std::string title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Oasis Engine", const unsigned int Width = 1280, unsigned int Height = 720)
			: title(title), Width(Width), Height(Height) {}

	};

	class OASIS_API Window {

	public:

		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& Callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};

}