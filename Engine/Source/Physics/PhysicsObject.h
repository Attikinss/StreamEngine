#pragma once
#include "Physics.h"
#include <glm/glm.hpp>

class b2Body;
class b2World;

namespace SE {
	class PhysicsObject {
		friend class PhysicsScene;

	public:
		PhysicsObject(b2World* world);
		~PhysicsObject();

		void SetBoxCollision(float density, float friction, float rest, float restThreshold, const glm::vec2& size, const glm::vec2& offset);
		void SetCircleCollision(float density, float friction, float rest, float restThreshold, float radius, const glm::vec2& offset);

		void ApplyForce(const glm::vec2& force, ForceType type = ForceType::FORCE);
		void ApplyForceToPoint(const glm::vec2& force, const glm::vec2& point, ForceType type = ForceType::FORCE);
		void ApplyTorque(float torque);

		void SetPosition(const glm::vec2& position);
		glm::vec2 GetPosition() const;

		void SetRotation(float rotation);
		float GetRotation() const;

		void SetBodyType(BodyType type);
		BodyType GetBodyType() const;

		void SetMass(float mass);
		float GetMass() const;

	private:
		b2Body* m_Body;
		b2World* m_World;
	};
}