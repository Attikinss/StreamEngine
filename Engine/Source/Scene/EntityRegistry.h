#pragma once
#include <entt/entt.hpp>

#include <vector>

namespace SE {
	class Entity;

	template<typename T>
	using ComponentCollection = entt::basic_view<entt::entity, entt::exclude_t<>, T>;

	class EntityRegistry {
	public:
		EntityRegistry();
		~EntityRegistry();

		uint32_t GenerateHandle();
		void Destroy(uint32_t handle);

		template<typename T, typename... Args>
		T& AddComponent(uint32_t handle, Args&&... args) {
			return m_Registry.emplace<T>((entt::entity)handle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent(uint32_t handle) {
			m_Registry.remove<T>((entt::entity)handle);
		}

		template<typename T>
		T& GetComponent(uint32_t handle) {
			return m_Registry.get<T>((entt::entity)handle);
		}

		template<typename T>
		bool TryGetComponent(uint32_t handle, T* out) {
			out = m_Registry.try_get<T>((entt::entity)handle);
			return out != nullptr;
		}

		template<typename T>
		bool HasComponent(uint32_t handle) {
			return m_Registry.any_of<T>((entt::entity)handle);
		}

		template<typename T>
		ComponentCollection<T> GetComponentsOfType() {
			return m_Registry.view<T>();
		}

	private:
		entt::registry m_Registry;
	};
}