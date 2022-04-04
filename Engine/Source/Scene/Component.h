#pragma once

namespace SE {
	class Component {
		friend class Entity;

	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void OnUpdate() = 0;
		virtual void OnFixedUpdate() = 0;

	public:
		bool IsEnabled = true;

	protected:
		Entity* m_Entity = nullptr;
	};
}