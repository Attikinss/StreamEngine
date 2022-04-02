#include "Renderer.h"
#include "GLStateManager.h"

#include <iostream>

namespace SE {
    bool Renderer::Initialize() {
        std::cout << "Renderer Initialized..." << std::endl;

        GLStateManager::InfoDump();
        return true;
    }

    bool Renderer::Shutdown() {
        std::cout << "Renderer Shutdown..." << std::endl;
        return true;
    }

    void Renderer::BeginFrame() {

    }

    void Renderer::EndFrame() {

    }

    void Renderer::Clear() {
        GLStateManager::Clear();
    }
}