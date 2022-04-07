#include "GraphicsContext.h"
#include "Core/Logger.h"

#include <GLFW/glfw3.h>

namespace SE {
	GraphicsContext::GraphicsContext(GLFWwindow* handle)
		: m_Handle(handle) {

		if (!s_Current) {
			SetCurrent();
		}
	}

	GraphicsContext::~GraphicsContext() {
		if (m_Handle) {
			glfwDestroyWindow(m_Handle);
		}

		// TODO: Ensure this context is the only before terminating GLFW
		glfwTerminate();
	}

	void GraphicsContext::SetCurrent() {
		if (!m_Handle) {
			Logger::Critical("Context handle is null! Context setting aborted.");

			// TODO: Assert
			return;
		}

		// TODO: Handle previous context
		s_Current = this;
		glfwMakeContextCurrent(m_Handle);
	}

	void GraphicsContext::Update() {
		if (!m_Handle) {
			Logger::Critical("Context handle is null, cannot update!");
			return;
		}

		glfwPollEvents();
		glfwSwapBuffers(m_Handle);
	}
}