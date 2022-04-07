#include "EntityRegistry.h"

namespace SE {
	EntityRegistry::EntityRegistry() {

	}

	EntityRegistry::~EntityRegistry() {
		m_Registry.clear();
	}

	uint32_t EntityRegistry::GenerateHandle() {
		return (uint32_t)m_Registry.create();
	}

	void EntityRegistry::Destroy(uint32_t handle) {
		m_Registry.destroy((entt::entity)handle);
	}
}