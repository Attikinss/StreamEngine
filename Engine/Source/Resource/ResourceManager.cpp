#include "StreamEnginePCH.h"
#include "ResourceManager.h"

namespace SE {
    ResourceManager& ResourceManager::Get() {
        static ResourceManager instance;

        return instance;
    }

    void ResourceManager::Initialize() {
        Logger::Trace("Resource Manager Initialized...");

        m_TextureLibrary.Initialize();
    }

    void ResourceManager::Shutdown() {
        m_TextureLibrary.Shutdown();

        Logger::Trace("Resource Manager Shutdown...");
    }
}