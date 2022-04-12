#include "StreamEnginePCH.h"
#include "Scene.h"
#include "Entity.h"
#include "EntityRegistry.h"

#include "Components/Component.h"
#include "Components/EntityInfo.h"
#include "Components/Transform2D.h"
#include "Components/WorldCamera.h"

#include <entt/entt.hpp>

namespace SE {
    Scene::Scene(const std::string& name)
        : m_Name(name), m_Registry(new EntityRegistry()) {
    }

    Scene::~Scene() {
        m_Selection.clear();
        delete m_Registry;
    }

    void Scene::Update() {
        auto transformView = m_Registry->GetComponentsOfType<Transform2D>();
        for (auto& entityID : transformView) {
            Entity entity(this, entityID);

            // Get component from view
            Transform2D& transform = entity.GetComponent<Transform2D>();
            if (!transform.IsEnabled) {
                continue;
            }

            transform.UpdateTransform();
        }

        auto cameraView = m_Registry->GetComponentsOfType<WorldCamera>();
        for (auto& entityID : cameraView) {
            Entity entity(this, entityID);

            // Get component from view
            WorldCamera& camera = entity.GetComponent<WorldCamera>();
            if (!camera.IsEnabled) {
                continue;
            }

            glm::mat4 transform = entity.GetComponent<Transform2D>().GetTransform();
            camera.GetCamera().SetView(glm::inverse(transform));
        }
    }

    void Scene::FixedUpdate() {

    }

    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity(this, m_Registry->GenerateHandle());
        entity.AddComponent<EntityInfo>().Name = name;
        entity.AddComponent<Transform2D>();

        return entity;
    }

    void Scene::DestroyEntity(Entity entity) {
        m_Registry->Destroy((entt::entity)entity.GetHandle());
    }
}