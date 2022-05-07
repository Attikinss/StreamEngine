#pragma once
#include <functional>
#include <sstream>
#include <string>

namespace SE {
#define BIND_FUNCTION(func) [this](auto&&... args) -> decltype(auto) { return func(std::forward<decltype(args)>(args)...); }

	class Event;
	using EventCallback = std::function<void(Event&)>;

	enum class EventType {
		TypeNone = 0,
		WindowClose, WindowResize, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MousePressed, MouseReleased, MouseMoved, MouseScrolled,
		FileDrop,
	};

	enum EventCategory {
		CategoryNone		= 0,
		CategoryApplication = 1 << 0,
		CategoryInput		= 1 << 1,
		CategoryKeyboard	= 1 << 2,
		CategoryMouse		= 1 << 3,
		CategoryMouseButton = 1 << 4
	};

	class Event {
	public:
		~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

	public:
		bool m_Used = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& evt)
			: m_Event(evt) {
		}

		template<typename T>
		bool Dispatch(const EventFunc<T>& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// Execute the function and mark as handled
				// if the event is blocked for further use
				m_Event.m_Used |= func(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& evt) {
		return stream << evt.ToString();
	}
}