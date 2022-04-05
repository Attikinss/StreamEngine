#pragma once
#include "Core/Logger.h"
#include "Components/Component.h"
#include "Scene.h"

#include <entt/entt.hpp>

namespace SE {
	class Entity {
	public:
		Entity() = default;
		Entity(Scene* scene, entt::entity handle);
		~Entity();

		void Destroy();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			if (HasComponent<T>()) {
				Logger::Error("Entity already has [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			Component& component = m_Scene->GetRegistry().AddComponent<T>(m_Handle, std::forward<Args>(args)...);
			return (T&)component;
		}

		template<typename T>
		void RemoveComponent() {
			if (!HasComponent()) {
				Logger::Error("Entity does not have [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			m_Scene->GetRegistry().RemoveComponent<T>(m_Handle);
		}

		template<typename T>
		T& GetComponent() {
			return m_Scene->GetRegistry().GetComponent<T>(m_Handle);
		}

		template<typename T>
		bool TryGetComponent(T* out) {
			return m_Scene->GetRegistry().TryGetComponent<T>(m_Handle, out);
		}

		template<typename T>
		bool HasComponent() {
			return m_Scene->GetRegistry().HasComponent<T>(m_Handle);
		}

		uint32_t GetHandle() const { return (uint32_t)m_Handle; }
		bool operator==(const Entity& other) const { return m_Handle == other.m_Handle; }
		bool operator!=(const Entity& other) const { return !(*this == other); }

	private:
		entt::entity m_Handle = entt::null;
		Scene* m_Scene;
	};
}