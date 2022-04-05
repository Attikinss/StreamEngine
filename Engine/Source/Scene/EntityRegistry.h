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

		entt::entity GenerateHandle();
		void Destroy(entt::entity handle);

		template<typename T, typename... Args>
		T& AddComponent(entt::entity handle, Args&&... args) {
			return m_Registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent(entt::entity handle) {
			m_Registry.remove<T>(handle);
		}

		template<typename T>
		T& GetComponent(entt::entity handle) {
			return m_Registry.get<T>(handle);
		}

		template<typename T>
		bool TryGetComponent(entt::entity handle, T* out) {
			out = m_Registry.try_get<T>(handle);
			return out != nullptr;
		}

		template<typename T>
		bool HasComponent(entt::entity handle) {
			return m_Registry.any_of<T>(handle);
		}

		template<typename T>
		ComponentCollection<T> GetComponentsOfType() {
			return m_Registry.view<T>();
		}

	private:
		entt::registry m_Registry;
	};
}