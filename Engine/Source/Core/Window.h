#pragma once
#include <string>

struct GLFWwindow;

namespace SE {
	class Window {
	public:
		Window(const std::string& title, int32_t width, int32_t height, bool fullscreen = false);
		~Window();

		void PollEvents();
		void SwapBuffers();

		bool ShouldClose() const;
		std::pair<float, float> GetSize() const;
		const std::string& GetTitle() const;
		GLFWwindow* GetHandle() const;

	private:
		GLFWwindow* m_WindowHandle;

		std::string m_Title;
		int32_t m_Width, m_Height;
		bool m_IsFullscreen;
	};
}