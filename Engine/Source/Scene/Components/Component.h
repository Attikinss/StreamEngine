#pragma once

namespace SE {
	class Component {
		friend class Entity;
		friend class Scene;

	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}

	public:
		bool IsEnabled = true;
	};
}