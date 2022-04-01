#include "GameApplication.h"

GameApplication::GameApplication() {
	m_Window = new SE::Window("Stream Engine", 1280, 720);
}

GameApplication::~GameApplication() {
	delete m_Window;
}

bool GameApplication::Initialize() {
	if (m_IsRunning) {
		// TODO: Out some info for debugging purposes
		return false;
	}

	// TODO: Initialize window
	return true;
}

void GameApplication::Run() {
	while (!m_Window->ShouldClose()) {
		m_Window->PollEvents();
		m_Window->SwapBuffers();
	}
}

bool GameApplication::Shutdown() {
	if (!m_IsRunning) {
		// TODO: Out some info for debugging purposes
		return false;
	}

	// TODO: Destroy window
	return true;
}
