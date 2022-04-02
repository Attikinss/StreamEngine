#include "Window.h"

#include <GLFW/glfw3.h>

namespace SE {
    static GLFWwindow* CreateWindow(const std::string& title, int32_t width, int32_t height, bool fullscreen) {
        // Initialize glfw if not already
        glfwInit();

        if (fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            return glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
        }

        GLFWwindow* windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(windowHandle);
        return windowHandle;
    }

    Window::Window(const std::string& title, int32_t width, int32_t height, bool fullscreen)
        : m_Title(title), m_Width(width), m_Height(height), m_IsFullscreen(fullscreen), m_WindowHandle(CreateWindow(title, width, height, fullscreen)) {

    }

    Window::~Window() {
        // Only destroy if it actally exists
        if (m_WindowHandle) {
            glfwDestroyWindow(m_WindowHandle);
            m_WindowHandle = nullptr;
        }

        // TODO: Move somewhere that makes sense
        glfwTerminate();
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }

    std::pair<float, float> Window::GetSize() const {
        return { (float)m_Width, (float)m_Height };
    }

    const std::string& Window::GetTitle() const {
        return m_Title;
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_WindowHandle);
    }
}