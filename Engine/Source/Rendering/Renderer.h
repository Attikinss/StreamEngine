#pragma once

namespace SE {
	class Renderer {
	public:
		static bool Initialize();
		static bool Shutdown();

		static void BeginFrame();
		static void EndFrame();
		static void Clear();
	};
}