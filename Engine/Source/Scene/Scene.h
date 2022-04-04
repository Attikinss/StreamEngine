#pragma once
#include "EntityRegistry.h"
#include <string>
#include <vector>

namespace SE {
	class Scene {
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		void Update();
		void FixedUpdate();

		Entity CreateEntity(const std::string& name = "Entity");
		void DestroyEntity(Entity entity);

		EntityRegistry& GetRegistry() { return m_Registry; }

	private:
		std::string m_Name;
		bool m_IsCurrent = false;
		
		EntityRegistry m_Registry;
		std::vector<Entity> m_Selection;
	};
}