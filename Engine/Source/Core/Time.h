#pragma once

namespace SE {
	class Time {
		friend class Application;

	private:
		static void Initialize();
		static void Update();

	public:
		static float GetTime();
		static float GetDeltaTime();
	};
}