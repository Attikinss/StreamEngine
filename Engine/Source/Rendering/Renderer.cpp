#include "Renderer.h"
#include "GLStateManager.h"

#include "Core/Logger.h"

namespace SE {
    bool Renderer::Initialize() {
        Logger::Trace("Renderer Initialised...");

        GLStateManager::InfoDump();
        GLStateManager::SetClearColour(0.15f, 0.15f, 0.15f);
        return true;
    }

    bool Renderer::Shutdown() {
        Logger::Trace("Renderer Shutdown...");
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