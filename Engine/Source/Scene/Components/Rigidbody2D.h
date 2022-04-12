#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace SE {
	class PhysicsObject;

	class Rigidbody2D : public Component {
		friend class Scene;

	public:
		Rigidbody2D() = default;
		~Rigidbody2D() {
			delete m_PhysObject;
		}

		static const char* GetName() { return "Rigidbody2D"; }

	public:
		bool IsKinematic = false;

	private:
		PhysicsObject* m_PhysObject = nullptr;
	};
}