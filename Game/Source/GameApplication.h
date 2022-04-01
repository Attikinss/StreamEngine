#pragma once
#include "Core/Application.h"

#include <string>

class GameApplication : public SE::Application {
public:
	GameApplication() = default;
	~GameApplication() = default;

	bool Initialize() override;
	void Run() override;
	bool Shutdown() override;
};