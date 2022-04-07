#include "Window.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace SE {
    static bool s_GLFWInitialized = false;

    static GLFWwindow* CreateGLFWWindow(const std::string& title, int32_t width, int32_t height, bool fullscreen) {
        // Initialize glfw if not already
        if (!s_GLFWInitialized && !glfwInit()) {
            Logger::Critical("GLFW failed to initialize correctly!");

            // TODO: Assert
            return nullptr;
        }

        // TODO: Parameterize version numbers
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            return glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
        }

        GLFWwindow* windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        return windowHandle;
    }

    Window::Window(const std::string& title, int32_t width, int32_t height, bool fullscreen)
        : m_Title(title), m_Width(width), m_Height(height), m_IsFullscreen(fullscreen), m_Context(CreateGLFWWindow(title, width, height, fullscreen)) {
        Logger::Trace("Window Created...");
    }

    Window::~Window() {
        Logger::Trace("Window Destroyed...");
    }
    
    void Window::Update() {
        m_Context.Update();
    }

    std::pair<float, float> Window::GetSize() const {
        return { (float)m_Width, (float)m_Height };
    }

    const std::string& Window::GetTitle() const {
        return m_Title;
    }

    GLFWwindow* Window::GetHandle() const {
        return m_Context.m_Handle;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Context.m_Handle);
    }
}