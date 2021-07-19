#pragma once

#include "Event.h"


namespace Oasis {

	class OASIS_API MouseMoveEvent : public Event {

	public:

		MouseMoveEvent(float MousePosX, float MousePosY) : m_MousePosX(MousePosX), m_MousePosY(MousePosY) {}

		inline float GetPosX() { return m_MousePosX; }
		inline float GetPosY() { return m_MousePosY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMoveEvent:(" << m_MousePosX << ',' << m_MousePosY << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:

		float m_MousePosX, m_MousePosY;

	};

	class OASIS_API MouseScrollEvent : public Event {

	public:

		MouseScrollEvent(float MouseOffsetX, float MouseOffsetY) : m_MouseOffsetX(MouseOffsetX), m_MouseOffsetY(MouseOffsetY) {}

		inline float GetOffsetX() { return m_MouseOffsetX; }
		inline float GetOffsetY() { return m_MouseOffsetY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrollEvent:(" << m_MouseOffsetX << ',' << m_MouseOffsetY << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	private:
		float m_MouseOffsetX, m_MouseOffsetY;

	};

	class OASIS_API MouseButtonEvent : public Event {

	public:

		inline int GetMouseButton() { return m_MouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput);

	protected:

		int m_MouseButton;
		
		MouseButtonEvent() {}
		MouseButtonEvent(int MouseButton) : m_MouseButton(MouseButton) {}

	};

	class OASIS_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(int MouseButton) : MouseButtonEvent(MouseButton) {};

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:" << m_MouseButton << '.';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed);

	};

	class OASIS_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:

		MouseButtonReleasedEvent(int MouseButton) : MouseButtonEvent(MouseButton) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:" << m_MouseButton << '.';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);

	};

}