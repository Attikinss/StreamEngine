#pragma once

namespace SE {
	class Application {
	public:
		Application() = default;
		~Application() = default;

		virtual bool Initialize() = 0;
		virtual void Run() = 0;
		virtual bool Shutdown() = 0;

	protected:
		bool m_IsRunning = false;
	};
}