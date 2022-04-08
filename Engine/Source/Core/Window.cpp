#include "StreamEnginePCH.h"
#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

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
        m_PtrData.Width = width;
        m_PtrData.Height = height;
        glfwSetWindowUserPointer(m_Context.m_Handle, &m_PtrData);

        SetCallbacks();

        Logger::Trace("Window Created...");
    }

    Window::~Window() {
        Logger::Trace("Window Destroyed...");
    }
    
    void Window::Update() {
        m_Context.Update();
    }

    void Window::SetEventCallback(const EventCallback& callback) {
        m_PtrData.Callback = callback;
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

    void Window::SetCallbacks() {
        // ------ Application event callbacks -----------------------
        glfwSetWindowSizeCallback(m_Context.m_Handle, [](GLFWwindow* handle, int32_t width, int32_t height) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Width = width;
            data.Height = height;
            data.Callback(WindowResizeEvent(width, height));
        });

        glfwSetWindowCloseCallback(m_Context.m_Handle, [](GLFWwindow* handle) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Callback(WindowCloseEvent());
        });

        glfwSetDropCallback(m_Context.m_Handle, [](GLFWwindow* handle, int32_t count, const char** filepaths) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Callback(FileDropEvent(count, filepaths));
        });

        // ------ Keyboard event callbacks --------------------------
        glfwSetKeyCallback(m_Context.m_Handle, [](GLFWwindow* handle, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);

            switch (action) {
                case GLFW_RELEASE: {
                    data.Callback(KeyReleasedEvent(key));
                    break;
                }
                
                case GLFW_PRESS: {
                    data.Callback(KeyPressedEvent(key, 0));
                    break;
                }

                case GLFW_REPEAT: {
                    // TODO: Track number of repeats
                    data.Callback(KeyPressedEvent(key, 1));
                    break;
                }

                default: break;
            }
        });

        glfwSetCharCallback(m_Context.m_Handle, [](GLFWwindow* handle, uint32_t charCode) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Callback(KeyTypedEvent(charCode));
        });

        // ------ Mouse event callbacks -----------------------------
        glfwSetMouseButtonCallback(m_Context.m_Handle, [](GLFWwindow* handle, int32_t button, int32_t action, int32_t mods) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            
            switch (action) {
                case GLFW_RELEASE: {
                    data.Callback(MouseButtonReleasedEvent(button));
                    break;
                }
                
                case GLFW_PRESS: {
                    data.Callback(MouseButtonPressedEvent(button));
                    break;
                }

                default: break;
            }
        });

        glfwSetCursorPosCallback(m_Context.m_Handle, [](GLFWwindow* handle, double x, double y) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Callback(MouseMovedEvent((float)x, (float)y));
        });

        glfwSetScrollCallback(m_Context.m_Handle, [](GLFWwindow* handle, double x, double y) {
            WindowDataPtr& data = *(WindowDataPtr*)glfwGetWindowUserPointer(handle);
            data.Callback(MouseScrolledEvent((float)x, (float)y));
        });
    }
}