#pragma once
#include <string>
#include <vector>

namespace SE {
	class Entity;
	class EntityRegistry;
	class PhysicsScene;

	class Scene {
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		Entity CreateEntity(const std::string& name = "Entity");
		void DestroyEntity(Entity entity);

		EntityRegistry& GetRegistry() const { return *m_Registry; }

		void Start();
		void Update();
		void FixedUpdate();

	private:
		std::string m_Name;
		bool m_IsCurrent = false;
		
		PhysicsScene* m_PhysicsScene = nullptr;
		EntityRegistry* m_Registry = nullptr;
		std::vector<Entity> m_Selection;
	};
}