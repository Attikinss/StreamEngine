#pragma once
#include <string>
#include <vector>

namespace SE {
	class Entity;
	class EntityRegistry;

	class Scene {
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		Entity CreateEntity(const std::string& name = "Entity");
		void DestroyEntity(Entity entity);
		void SetCurrent();

		EntityRegistry& GetRegistry() const { return *m_Registry; }

		static void Update();
		static void FixedUpdate();

	private:
		std::string m_Name;
		bool m_IsCurrent = false;
		
		EntityRegistry* m_Registry = nullptr;
		std::vector<Entity> m_Selection;

		inline static Scene* s_CurrentScene = nullptr;
	};
}