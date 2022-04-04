#include "Scene.h"
#include "Entity.h"

namespace SE {
    Scene::Scene(const std::string& name)
        : m_Name(name) {
    }

    Scene::~Scene() {
        m_Selection.clear();
    }

    void Scene::Update() {
        
    }

    void Scene::FixedUpdate() {

    }

    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity(this, m_Registry.GenerateHandle());
        // TODO: Add entity info and transform

        return entity;
    }

    void Scene::DestroyEntity(Entity entity) {
        m_Registry.Destroy((entt::entity)entity.GetHandle());
    }
}