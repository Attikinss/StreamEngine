#include "StreamEnginePCH.h"
#include "Application.h"
#include "Input.h"
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
		delete m_LayerStack;
		m_Window = nullptr;
		m_LayerStack = nullptr;
	}

	bool Application::Initialize() {
		if (m_IsRunning) {
			Logger::Error("Application is already running! Initialization process aborted.");
			return false;
		}

		Logger::Initialize();
		Input::Initialize();
		Time::Initialize();
		m_LayerStack = new LayerStack();

		m_Window = new SE::Window("Stream Engine", 1280, 720);
		m_Window->SetEventCallback(BIND_FUNCTION(Application::OnEvent));
		if (!Renderer::Initialize()) {
			Logger::Critical("Renderer failed to initialize correctly!");
			return false;
		}

		return m_IsRunning = true;
	}

	void Application::Run() {
		if (!m_IsRunning) {
			Logger::Critical("Application has not been initialized! Runtime aborted.");
			return;
		}

		while (!m_ShutdownRequested) {
			OnUpdate();

			// Update all layers
			for (Layer* layer : *m_LayerStack) {
				layer->Update();
			}

			// Render all layers
			for (Layer* layer : *m_LayerStack) {
				layer->Render();
			}
		}
	}

	bool Application::Shutdown() {
		if (!m_IsRunning) {
			Logger::Error("Application is not running! Shutdown process aborted.");
			return false;
		}

		if (!Renderer::Shutdown()) {
			Logger::Critical("Renderer failed to shutdown correctly!");
			return false;
		}

		delete m_Window;
		delete m_LayerStack;
		m_Window = nullptr;
		m_LayerStack = nullptr;

		m_IsRunning = false;
		return true;
	}

	void Application::AttachLayer(Layer* layer) {
		if (!layer) {
			Logger::Error("Layer attachment failed! Layer is null.");
			return;
		}

		if (!m_LayerStack) {
			Logger::Error("Layer stack not initialized! Layer ({}) attachment aborted.", layer->GetNane());
			return;
		}
		
		m_LayerStack->AttachLayer(layer);
	}

	void Application::DetachLayer(Layer* layer) {
		if (!layer) {
			Logger::Error("Layer detachment failed! Layer is null.");
			return;
		}

		if (!m_LayerStack) {
			Logger::Error("Layer stack not initialized! Layer ({}) detachment aborted.", layer->GetNane());
			return;
		}

		m_LayerStack->DetachLayer(layer);
	}

	const Window& Application::GetWindow() const {
		return *m_Window;
	}

	Application& Application::Get() {
		return *s_Instance;
	}

	void Application::OnEvent(Event& evt) {
		if (evt.GetEventType() == EventType::WindowClose) {
			m_ShutdownRequested = true;
			return;
		}
	}

	void Application::OnUpdate() {
		m_Window->Update();
		
		Input::Update();
		Time::Update();
	}
}