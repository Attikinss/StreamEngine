#pragma once
#include "PhysicsObject.h"
#include <glm/glm.hpp>

class b2World;

namespace SE {
	class PhysicsScene {
	public:
		PhysicsScene(const glm::vec2& gravity);
		~PhysicsScene();

		PhysicsObject* CreatePhysicsObject(PhysicsObjectData data = PhysicsObjectData());

		void Step();
		void SetGravity(const glm::vec2& gravity);
		glm::vec2 GetGravity() const;

	private:
		b2World* m_World;
	};
}