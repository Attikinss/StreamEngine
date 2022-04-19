#pragma once
#include "Component.h"
#include "Physics/Physics.h"
#include <glm/glm.hpp>

namespace SE {
	class PhysicsObject;

	class Rigidbody2D : public Component {
		friend class Scene;

	public:
		Rigidbody2D() = default;
		~Rigidbody2D();

		static const char* GetName() { return "Rigidbody2D"; }

		void ApplyForce(const glm::vec2& force, ForceType type = ForceType::FORCE);
		void ApplyForceToPoint(const glm::vec2& force, const glm::vec2& point, ForceType type = ForceType::FORCE);
		void ApplyTorque(float torque);

		void SetPosition(const glm::vec2& position);
		void SetRotation(float rotation);

		void Move(const glm::vec2& delta);
		void Rotate(float delta);

	public:
		PhysicsObjectData PhysicsData;

	private:
		PhysicsObject* m_PhysObject = nullptr;
	};
}