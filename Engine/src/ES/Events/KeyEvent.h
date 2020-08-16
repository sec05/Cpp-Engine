#pragma once

#include "Event.h"


namespace ES
{
	class   KeyEvent : public Event //gets and returns the keycode of pressed key
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		int m_KeyCode;
	};

	class   KeyPressedEvent : public KeyEvent//gets pressed key and how many times it was repeated
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class   KeyReleasedEvent : public KeyEvent//gets released key
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();

		}
		
		EVENT_CLASS_TYPE(KeyReleased)
	};

	class   KeyTypedEvent : public KeyEvent//gets pressed key and how many times it was repeated
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	private:
		int m_RepeatCount;
	};
}