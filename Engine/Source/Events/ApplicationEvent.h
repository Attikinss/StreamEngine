#pragma once
#include "Event.h"

namespace SE {
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {
		}

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowResize"; }
		int GetCategoryFlags() const override { return EventCategory::CategoryApplication; }

		std::pair<uint32_t, uint32_t> GetSize() const { return { m_Width, m_Height }; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return stream.str();
		}

	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "WindowClose"; }
		int GetCategoryFlags() const override { return EventCategory::CategoryApplication; }
		std::string ToString() const override { return std::string("WindowCloseEvent"); }
	};

	class FileDropEvent : public Event {
	public:
		FileDropEvent(int32_t count, const char** paths)
			: m_PathCount(count) {
			m_Paths.reserve(count);
			for (uint32_t i = 0; i < count; i++) {
				m_Paths.emplace_back(paths[i]);
			}
		}

		static EventType GetStaticType() { return EventType::FileDrop; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "FileDrop"; }
		int GetCategoryFlags() const override { return EventCategory::CategoryApplication; }

		std::vector<std::string> GetFilepaths() const { return m_Paths; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "FileDropEvent:";

			for (auto path : m_Paths) {
				stream << "\n\t" << path;
			}

			return stream.str();
		}

	private:
		int32_t m_PathCount;
		std::vector<std::string> m_Paths;
	};
}