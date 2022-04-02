#pragma once
#include "Window.h"

namespace SE {
	class Application {
	public:
		Application();
		~Application();

		bool Initialize();
		void Run();
		bool Shutdown();

	protected:
		Window* m_Window = nullptr;
		bool m_IsRunning = false;
	};
}