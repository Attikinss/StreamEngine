#include "GameApplication.h"

bool GameApplication::Initialize() {
	if (m_IsRunning) {
		// TODO: Out some info for debugging purposes
		return false;
	}

	// TODO: Initialize window
	return true;
}

void GameApplication::Run() {
	while (true);
}

bool GameApplication::Shutdown() {
	if (!m_IsRunning) {
		// TODO: Out some info for debugging purposes
		return false;
	}

	// TODO: Destroy window
	return true;
}
