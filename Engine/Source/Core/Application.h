#pragma once
#include "LayerStack.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"

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

		void AttachLayer(Layer* layer);
		void DetachLayer(Layer* layer);

		const Window& GetWindow() const;
		static Application& Get();

	private:
		void OnEvent(Event& evt);
		void OnUpdate();

	protected:
		Window* m_Window = nullptr;
		LayerStack* m_LayerStack = nullptr;

		bool m_IsRunning = false;
		bool m_ShutdownRequested = false;

		inline static Application* s_Instance = nullptr;
	};
}