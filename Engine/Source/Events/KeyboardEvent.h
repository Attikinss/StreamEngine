#pragma once
#include "Event.h"

namespace SE {
	class KeyboardEvent : public Event {
	protected:
		KeyboardEvent(int keycode)
			: m_KeyCode(keycode) {
		}

	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		int GetCategoryFlags() const override { return EventCategory::CategoryKeyboard | EventCategory::CategoryInput; }

	protected:
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyboardEvent {
	public:
		KeyPressedEvent(int keycode, uint32_t repeatCount)
			: KeyboardEvent(keycode), m_RepeatCount(repeatCount) {
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KeyPressed"; }

		uint32_t GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return stream.str();
		}

	private:
		uint32_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyboardEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyboardEvent(keycode) {
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KeyReleased"; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "KeyReleasedEvent: " << m_KeyCode;
			return stream.str();
		}
	};

	class KeyTypedEvent : public KeyboardEvent {
	public:
		KeyTypedEvent(int keycode)
			: KeyboardEvent(keycode) {
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "KeyTyped"; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "KeyTypedEvent: " << m_KeyCode;
			return stream.str();
		}
	};
}