#include "StreamEnginePCH.h"
#include "Scene.h"
#include "Entity.h"
#include "EntityRegistry.h"

#include "Components/Collider.h"
#include "Components/EntityInfo.h"
#include "Components/Rigidbody2D.h"
#include "Components/SpriteAnimator.h"
#include "Components/SpriteRenderer.h"
#include "Components/Transform2D.h"
#include "Components/WorldCamera.h"

#include "Physics/PhysicsObject.h"
#include "Physics/PhysicsScene.h"

#include "Rendering/Quad.h"
#include "Rendering/Renderer.h"

#include "Core/Time.h"

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

            if (entity.HasComponent<BoxCollider2D>()) {
                BoxCollider2D& collider = entity.GetComponent<BoxCollider2D>();

                rigidbody.m_PhysObject->SetBoxCollision(collider.Density, collider.Friction, collider.Restitution,
                    collider.RestitutionThreshold, collider.Size * transform.Scale, collider.Offset);
            }

            if (entity.HasComponent<CircleCollider>()) {
                CircleCollider& collider = entity.GetComponent<CircleCollider>();

                float radiusMod = fmaxf(transform.Scale.x, transform.Scale.y);
                rigidbody.m_PhysObject->SetCircleCollision(collider.Density, collider.Friction, collider.Restitution,
                    collider.RestitutionThreshold, collider.Radius * radiusMod, collider.Offset);
            }
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

        auto spriteRendererView = m_Registry->GetComponentsOfType<SpriteRenderer>();
        for (auto& entityID : spriteRendererView) {
            Entity entity(this, entityID);

            // Get component from view
            SpriteRenderer& renderer = entity.GetComponent<SpriteRenderer>();
            Transform2D& transform = entity.GetComponent<Transform2D>();
            if (!renderer.IsEnabled) {
                continue;
            }

            if (entity.HasComponent<SpriteAnimator>()) {
                SpriteAnimator& animator = entity.GetComponent<SpriteAnimator>();
                if (animator.IsEnabled && animator.Animate) {
                    animator.NextFrame(Time::GetDeltaTime());
                }
            }
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
            float rotation = -physObject->GetRotation();

            rigidbody.PhysicsData.Position = position;
            rigidbody.PhysicsData.Rotation = rotation;

            transform.Position = position;
            transform.Rotation = rotation;
        }

        m_PhysicsScene->Step();
    }

    void Scene::Render() {
        // TODO: Use highest priority camera rather than first
        auto cameraView = m_Registry->GetComponentsOfType<WorldCamera>();
        if (cameraView.empty()) {
            return;
        }

        for (auto& entityID : cameraView) {
            Entity entity(this, entityID);

            // Use first active camera
            WorldCamera& camera = entity.GetComponent<WorldCamera>();
            if (camera.IsEnabled) {
                Render(camera.GetCamera());
                break;
            }
        }
    }

    void Scene::Render(const Camera& camera) {
        Renderer::BeginFrame(camera);

        auto spriteRendererView = m_Registry->GetComponentsOfType<SpriteRenderer>();
        for (auto& entityID : spriteRendererView) {
            Entity entity(this, entityID);

            // Get component from view
            SpriteRenderer& renderer = entity.GetComponent<SpriteRenderer>();
            Transform2D& transform = entity.GetComponent<Transform2D>();
            if (!renderer.IsEnabled) {
                continue;
            }

            // Create quad and assign color
            Quad quad;
            quad.SetColor(renderer.Color);

            if (renderer.FlipX) {
                quad.FlipX();
            }

            if (renderer.FlipY) {
                quad.FlipY();
            }

            if (entity.HasComponent<SpriteAnimator>()) {
                SpriteAnimator& animator = entity.GetComponent<SpriteAnimator>();
                if (animator.IsEnabled && animator.Animate) {
                    auto [min, max] = animator.GetFrameCoords();
                    quad.Vertices[0].UV = { min.x, min.y + max.y };
                    quad.Vertices[1].UV = { min.x, min.y };
                    quad.Vertices[2].UV = { min.x + max.x, min.y };
                    quad.Vertices[3].UV = { min.x + max.x, min.y + max.y };
                }
            }

            Renderer::Submit(renderer, transform.GetTransform(), quad);
        }

        Renderer::EndFrame();
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