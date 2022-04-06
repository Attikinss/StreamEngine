#include "Scene.h"
#include "Entity.h"

#include "Components/Component.h"
#include "Components/EntityInfo.h"
#include "Components/Transform2D.h"
#include "Components/WorldCamera.h"

#include <entt/entt.hpp>

namespace SE {
    Scene::Scene(const std::string& name)
        : m_Name(name) {
        if (s_CurrentScene == nullptr) {
            s_CurrentScene = this;
        }
    }

    Scene::~Scene() {
        m_Selection.clear();
    }

    void Scene::Update() {
        if (s_CurrentScene == nullptr) {
            return;
        }

        auto transformView = s_CurrentScene->m_Registry.GetComponentsOfType<Transform2D>();
        for (auto& entity : transformView) {
            // Get component from view
            Transform2D& transform = transformView.get<Transform2D>(entity);
            if (!transform.IsEnabled) {
                continue;
            }

            transform.UpdateTransform();
        }

        auto cameraView = s_CurrentScene->m_Registry.GetComponentsOfType<WorldCamera>();
        for (auto& entity : cameraView) {
            // Get component from view
            WorldCamera& camera = cameraView.get<WorldCamera>(entity);
            if (!camera.IsEnabled) {
                continue;
            }

            glm::mat4 transform = transformView.get<Transform2D>(entity).GetTransform();
            camera.GetCamera().SetView(glm::inverse(transform));
        }
    }

    void Scene::FixedUpdate() {
        if (s_CurrentScene == nullptr) {
            return;
        }
    }

    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity(this, m_Registry.GenerateHandle());
        entity.AddComponent<EntityInfo>().Name = name;
        entity.AddComponent<Transform2D>();

        return entity;
    }

    void Scene::DestroyEntity(Entity entity) {
        m_Registry.Destroy((entt::entity)entity.GetHandle());
    }

    void Scene::SetCurrent() {
        // TODO: Unload previous scene
        s_CurrentScene = this;
    }
}