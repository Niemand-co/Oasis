#pragma once

#include "Event.h"

#include <sstream>

namespace Oasis {

	class WindowResizeEvent : public Event {

	public:
		WindowResizeEvent(int Width, int Height) : m_Width(Width), m_Height(Height) {}

		inline int GetWindowWidth() { return m_Width; }
		inline int GetWindowHeight() { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent:(" << m_Width << ',' << m_Height << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		unsigned int m_Width, m_Height;

	};

	class OASIS_API WindowCloseEvent : public Event {

	public:

		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	};

	class OASIS_API AppTickEvent : public Event {

	public:

		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	};

	class OASIS_API AppRenderEvent : public Event {

	public:

		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender);

	};

	class OASIS_API AppUpdateEvent : public Event {

	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

}