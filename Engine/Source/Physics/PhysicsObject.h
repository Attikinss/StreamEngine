#pragma once

#include <glm/glm.hpp>

class b2Body;
class b2World;

namespace SE {
	enum class BodyType {
		DYNAMIC = 0,
		KINEMATIC,
		STATIC
	};

	struct PhysicsObjectData {
		glm::vec2 Position = { 0.0f, 0.0f };
		float Rotation = 0.0f;
		float Mass = 1.0f;
		bool FixedRotation = false;
		BodyType Type = BodyType::DYNAMIC;
	};

	class PhysicsObject {
		friend class PhysicsScene;

	public:
		PhysicsObject(b2World* world);
		~PhysicsObject();

		void SetBoxCollision(float density, float friction, float rest, float restThreshold, const glm::vec2& size, const glm::vec2& offset);
		void SetCircleCollision(float density, float friction, float rest, float restThreshold, float radius, const glm::vec2& offset);

		void SetBodyType(BodyType type);
		glm::vec2 GetPosition();
		float GetRotation();

	private:
		b2Body* m_Body;
		b2World* m_World;
	};
}