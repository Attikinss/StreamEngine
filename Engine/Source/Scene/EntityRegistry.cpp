#include "StreamEnginePCH.h"
#include "EntityRegistry.h"

namespace SE {
	EntityRegistry::EntityRegistry() {

	}

	EntityRegistry::~EntityRegistry() {
		m_Registry.clear();
	}

	entt::entity EntityRegistry::GenerateHandle() {
		return m_Registry.create();
	}

	void EntityRegistry::Destroy(entt::entity handle) {
		m_Registry.destroy(handle);
	}
}