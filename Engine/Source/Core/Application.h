#pragma once
#include "Window.h"

namespace SE {
	struct CommandLineArgs {
		char** Args = nullptr;
		int32_t ArgsCount = 0;

		CommandLineArgs() = default;
		CommandLineArgs(char** args, int32_t count)
			: Args(args), ArgsCount(count) {
		}

		const char* operator[](int32_t index) const {
			_ASSERT(index < ArgsCount);
			return Args[index];
		}
	};

	class Application {
	private:
		Application(CommandLineArgs args);

	public:
		static Application* Create(CommandLineArgs args = CommandLineArgs());
		~Application();

		bool Initialize();
		void Run();
		bool Shutdown();

		const Window& GetWindow() const;
		static Application& Get();

	private:
		void OnUpdate();

	protected:
		Window* m_Window = nullptr;
		bool m_IsRunning = false;

		inline static Application* s_Instance = nullptr;
	};
}