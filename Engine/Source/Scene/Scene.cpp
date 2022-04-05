#include "Scene.h"
#include "Entity.h"

#include "Components/Component.h"
#include "Components/EntityInfo.h"
#include "Components/Transform2D.h"

#include <entt/entt.hpp>

namespace SE {
    Scene::Scene(const std::string& name)
        : m_Name(name) {
    }

    Scene::~Scene() {
        m_Selection.clear();
    }

    void Scene::Update() {
        auto transformView = m_Registry.GetComponentsOfType<Transform2D>();
        for (auto& entity : transformView) {
            // Get component from view
            Transform2D& transform = transformView.get<Transform2D>(entity);
            if (!transform.IsEnabled) {
                continue;
            }

            transform.UpdateTransform();
        }
    }

    void Scene::FixedUpdate() {

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
}