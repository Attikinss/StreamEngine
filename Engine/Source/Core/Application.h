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

	protected:
		Window* m_Window = nullptr;
		bool m_IsRunning = false;

		inline static Application* s_Instance = nullptr;
	};
}