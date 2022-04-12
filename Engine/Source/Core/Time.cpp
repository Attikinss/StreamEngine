#include "StreamEnginePCH.h"
#include "Time.h"

namespace SE {
    struct TimeInfo {
        float CurrentTime = 0.0f;
        float DeltaTime = 0.0f;
        float PreviousTime = 0.0f;

        std::chrono::time_point<std::chrono::high_resolution_clock> InitTime;
    };

    static TimeInfo s_Info;

    static float GetElapsedTime() {
        return (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - s_Info.InitTime).count() * 0.001 * 0.001 * 0.001);
    }

    void Time::Initialize() {
        s_Info.InitTime = std::chrono::high_resolution_clock::now();
        Logger::Trace("Time Initialized...");
    }

    void Time::Update() {
        s_Info.CurrentTime = GetElapsedTime();
        s_Info.DeltaTime = s_Info.CurrentTime - s_Info.PreviousTime;
        s_Info.PreviousTime = s_Info.CurrentTime;
    }

    float Time::GetTime() {
        return s_Info.CurrentTime;
    }

    float Time::GetDeltaTime() {
        return s_Info.DeltaTime;
    }
}