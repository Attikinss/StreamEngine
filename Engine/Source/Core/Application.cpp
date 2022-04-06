#include "Application.h"
#include "Input.h"
#include "Logger.h"
#include "Time.h"

#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Scene/Scene.h"

namespace SE {
	Application* Application::Create(CommandLineArgs args) {
		return s_Instance ? nullptr : new Application(args);
	}

	Application::Application(CommandLineArgs args) {
		s_Instance = this;

		for (uint32_t i = 0; i < args.ArgsCount; i++) {
			// Compare strings against map of [command, action]
		}
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

		Input::Initialize();
		Time::Initialize();

		m_Window = new SE::Window("Stream Engine", 1280, 720);
		return true;
	}

	void Application::Run() {
		Camera cam(1280.0f, 720.0f);

		while (!m_Window->ShouldClose()) {
			OnUpdate();
			Renderer::BeginFrame(cam);

			/* Submit sprites here */

			Renderer::EndFrame();
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

	void Application::OnUpdate() {
		m_Window->PollEvents();
		m_Window->SwapBuffers();
		
		Input::Update();
		Time::Update();

		// TODO: Update user made components

		Scene::Update();
	}
}