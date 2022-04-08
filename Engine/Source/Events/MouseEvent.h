#pragma once
#include "Event.h"

namespace SE {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput; }
		const char* GetName() const override { return "MouseMoved"; }

		std::pair<float, float> GetPosition() const { return { m_MouseX, m_MouseY }; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return stream.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_OffsetX(xOffset), m_OffsetY(yOffset) {
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput; }
		const char* GetName() const override { return "MouseScrolled"; }

		std::pair<float, float> GetOffset() const { return { m_OffsetX, m_OffsetY }; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return stream.str();
		}

	private:
		float m_OffsetX, m_OffsetY;
	};

	class MouseButtonEvent : public Event {
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {
		}

	public:
		int GetMouseButton() const { return m_Button; }
		int GetCategoryFlags() const override { return EventCategory::CategoryMouse | EventCategory::CategoryInput | EventCategory::CategoryMouseButton; }

	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {
		}

		static EventType GetStaticType() { return EventType::MousePressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MousePressed"; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "MouseButtonPressedEvent: " << m_Button;
			return stream.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}

		static EventType GetStaticType() { return EventType::MouseReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "MouseReleased"; }

		std::string ToString() const override {
			std::ostringstream stream;
			stream << "MouseButtonReleasedEvent: " << m_Button;
			return stream.str();
		}
	};
}