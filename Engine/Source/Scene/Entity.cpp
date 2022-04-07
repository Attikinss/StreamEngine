#include "Entity.h"

#include <entt/entt.hpp>

namespace SE {
	Entity::Entity()
		: m_Handle((uint32_t)entt::null) {

	}

	Entity::Entity(Scene* scene, uint32_t handle)
		: m_Scene(scene), m_Handle(handle) {

	}

	Entity::~Entity() {
		m_Scene = nullptr;
	}

	void Entity::Destroy() {
		m_Scene->DestroyEntity(*this);
	}
}