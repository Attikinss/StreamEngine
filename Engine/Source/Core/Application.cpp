#include "Application.h"
#include "Logger.h"

#include "Renderer/Renderer.h"

namespace SE {
	Application* Application::Create() {
		return s_Instance ? nullptr : new Application();
	}

	Application::Application() {
		m_Window = new SE::Window("Stream Engine", 1280, 720);
		s_Instance = this;
	}

	Application::~Application() {
		s_Instance = nullptr;
		delete m_Window;
	}

	bool Application::Initialize() {
		if (m_IsRunning) {
			// TODO: Out some info for debugging purposes
			return false;
		}

		Logger::Initialize();
		if (Renderer::Initialize()) {
			// TODO: Notify user of error
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

		if (Renderer::Shutdown()) {
			// TODO: Notify user of error
		}

		// TODO: Destroy window
		return true;
	}

	const Window& Application::GetWindow() const {
		return *m_Window;
	}

	Application& Application::Get() {
		return *s_Instance;
	}
}