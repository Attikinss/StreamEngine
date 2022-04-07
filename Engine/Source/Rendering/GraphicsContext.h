#pragma once
struct GLFWwindow;

namespace SE {
	class GraphicsContext {
		friend class Window;

	public:
		GraphicsContext() = default;
		GraphicsContext(GLFWwindow* handle);
		~GraphicsContext();

		void SetCurrent();
		void Update();

	private:
		GLFWwindow* m_Handle = nullptr;
		inline static GraphicsContext* s_Current = nullptr;
	};
}