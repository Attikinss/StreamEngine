#include "Entity.h"

namespace SE {
	Entity::Entity(Scene* scene, entt::entity handle)
		: m_Scene(scene), m_Handle(handle) {

	}

	Entity::~Entity() {
		m_Scene = nullptr;
	}

	void Entity::SetEnabled(bool enabled) {
		IsEnabled = enabled;
	}

	void Entity::Destroy() {
		m_Scene->DestroyEntity(*this);
	}
}