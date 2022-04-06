#pragma once
#include "Window.h"

namespace SE {
	class Application {
	private:
		Application();

	public:
		static Application* Create();
		~Application();

		bool Initialize();
		void Run();
		bool Shutdown();

		const Window& GetWindow() const;
		static Application& Get();

	protected:
		Window* m_Window = nullptr;
		bool m_IsRunning = false;

		inline static Application* s_Instance = nullptr;
	};
}