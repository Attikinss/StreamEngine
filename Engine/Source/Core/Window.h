#pragma once
#include "Rendering/GraphicsContext.h"
#include "Events/Event.h"

#include <string>

struct GLFWwindow;

namespace SE {
	class Window {
	private:
		struct WindowDataPtr {
			uint32_t Width = 0, Height = 0;
			EventCallback Callback = EventCallback();
		};

	public:
		Window(const std::string& title, int32_t width, int32_t height, bool fullscreen = false);
		~Window();

		void Update();
		void SetEventCallback(const EventCallback& callback);
		bool ShouldClose() const;


		std::pair<float, float> GetSize() const;
		const std::string& GetTitle() const;
		GLFWwindow* GetHandle() const;

	private:
		void SetCallbacks();

	private:
		GraphicsContext m_Context;
		WindowDataPtr m_PtrData;

		std::string m_Title;
		int32_t m_Width, m_Height;
		bool m_IsFullscreen;
	};
}