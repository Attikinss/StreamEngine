#pragma once

namespace SE {
	class Time {
		friend class Application;

	private:
		static void Initialize();
		static void Update();

	public:
		static double GetTime();
		static double GetDeltaTime();
	};
}