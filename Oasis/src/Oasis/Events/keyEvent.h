#pragma once

#include "Event.h"

#include <sstream>

namespace Oasis {
	
	class OASIS_API KeyEvent : public Event{

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		int m_KeyCode;

		KeyEvent(){}
		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}

	};

	class OASIS_API KeyPressedEvent : public KeyEvent {
	public:

		KeyPressedEvent(int KeyCode, int RepeatCount) : KeyEvent(KeyCode), m_KeyRepeatCount(RepeatCount) {}

		inline int GetRepeatCount() { return m_KeyRepeatCount; }

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << '(' << m_KeyRepeatCount << "Repeats).";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_KeyRepeatCount;

	};

	class OASIS_API KeyReleasedEvent : public KeyEvent {
	public:

		KeyReleasedEvent(int KeyCode) : KeyEvent(KeyCode) {}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode << '.';
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

	class OASIS_API KeyTypeEvent : public KeyEvent {

	public:

		KeyTypeEvent(int KeyCode) : KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypeEvent:" << m_KeyCode << '.';
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	};

}