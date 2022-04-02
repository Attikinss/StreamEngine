#include "Application.h"

namespace SE {
	Application::Application() {
		m_Window = new SE::Window("Stream Engine", 1280, 720);
	}

	Application::~Application() {
		delete m_Window;
	}

	bool Application::Initialize() {
		if (m_IsRunning) {
			// TODO: Out some info for debugging purposes
			return false;
		}

		// TODO: Initialize window
		return true;
	}

	void Application::Run() {
		while (!m_Window->ShouldClose()) {
			m_Window->PollEvents();
			m_Window->SwapBuffers();
		}
	}

	bool Application::Shutdown() {
		if (!m_IsRunning) {
			// TODO: Out some info for debugging purposes
			return false;
		}

		// TODO: Destroy window
		return true;
	}
}