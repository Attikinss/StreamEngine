#pragma once
#include "Core/Application.h"
#include "Core/Window.h"

#include <string>

class GameApplication : public SE::Application {
public:
	// TODO: Pass in application args struct or something
	GameApplication();
	~GameApplication();

	bool Initialize() override;
	void Run() override;
	bool Shutdown() override;

private:
	SE::Window* m_Window;
};