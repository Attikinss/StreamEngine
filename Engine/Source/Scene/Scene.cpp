#include "StreamEnginePCH.h"
#include "Scene.h"
#include "Entity.h"
#include "EntityRegistry.h"

#include "Components/Collider.h"
#include "Components/EntityInfo.h"
#include "Components/Rigidbody2D.h"
#include "Components/Transform2D.h"
#include "Components/WorldCamera.h"

#include "Physics/PhysicsObject.h"
#include "Physics/PhysicsScene.h"

#include <entt/entt.hpp>

namespace SE {
    Scene::Scene(const std::string& name)
        : m_Name(name), m_Registry(new EntityRegistry()) {
    }

    Scene::~Scene() {
        m_Selection.clear();
        delete m_Registry;
        m_Registry = nullptr;

        delete m_PhysicsScene;
        m_PhysicsScene = nullptr;
    }

    void Scene::Start() {
        m_PhysicsScene = new PhysicsScene({ 0.0f, -9.81f });

        auto rigidbodyView = m_Registry->GetComponentsOfType<Rigidbody2D>();
        for (auto& entityID : rigidbodyView) {
            Entity entity(this, entityID);

            if (!entity.HasComponent<Rigidbody2D>()) {
                continue;
            }

            // Get component from view
            Rigidbody2D& rigidbody = entity.GetComponent<Rigidbody2D>();
            Transform2D& transform = entity.GetComponent<Transform2D>();

            rigidbody.PhysicsData.Position = transform.Position;
            rigidbody.PhysicsData.Rotation = transform.Rotation;

            rigidbody.m_PhysObject = m_PhysicsScene->CreatePhysicsObject(rigidbody.PhysicsData);
        }

        auto boxColliderView = m_Registry->GetComponentsOfType<BoxCollider2D>();
        for (auto& entityID : rigidbodyView) {
            Entity entity(this, entityID);

            if (!entity.HasComponent<BoxCollider2D>()) {
                continue;
            }

            // Get components from view
            BoxCollider2D& collider = entity.GetComponent<BoxCollider2D>();
            Rigidbody2D& rigidbody = entity.GetComponent<Rigidbody2D>();
            Transform2D& transform = entity.GetComponent<Transform2D>();

            rigidbody.m_PhysObject->SetBoxCollision(collider.Density, collider.Friction, collider.Restitution,
                collider.RestitutionThreshold, collider.Size * transform.Scale, collider.Offset);
        }

        auto circleColliderView = m_Registry->GetComponentsOfType<CircleCollider>();
        for (auto& entityID : rigidbodyView) {
            Entity entity(this, entityID);

            if (!entity.HasComponent<CircleCollider>()) {
                continue;
            }

            // Get components from view
            CircleCollider& collider = entity.GetComponent<CircleCollider>();
            Rigidbody2D& rigidbody = entity.GetComponent<Rigidbody2D>();
            Transform2D& transform = entity.GetComponent<Transform2D>();

            float radiusMod = fmaxf(transform.Scale.x, transform.Scale.y);
            rigidbody.m_PhysObject->SetCircleCollision(collider.Density, collider.Friction, collider.Restitution,
                collider.RestitutionThreshold, collider.Radius * radiusMod, collider.Offset);
        }
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
        auto rigidbodyView = m_Registry->GetComponentsOfType<Rigidbody2D>();
        for (auto& entityID : rigidbodyView) {
            Entity entity(this, entityID);

            // Get component from view
            Rigidbody2D& rigidbody = entity.GetComponent<Rigidbody2D>();
            Transform2D& transform = entity.GetComponent<Transform2D>();
            if (!transform.IsEnabled || !rigidbody.IsEnabled) {
                continue;
            }

            PhysicsObject* physObject = rigidbody.m_PhysObject;
            physObject->SetMass(rigidbody.PhysicsData.Mass);
            physObject->SetBodyType(rigidbody.PhysicsData.Type);

            glm::vec2 position = physObject->GetPosition();
            float rotation = physObject->GetRotation();

            rigidbody.PhysicsData.Position = position;
            rigidbody.PhysicsData.Rotation = rotation;

            transform.Position = position;
            transform.Rotation = rotation;
        }

        m_PhysicsScene->Step();
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