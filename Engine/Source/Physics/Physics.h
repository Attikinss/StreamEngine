#pragma once
#include <glm/glm.hpp>

namespace SE {
	enum class BodyType {
		DYNAMIC = 0,
		KINEMATIC,
		STATIC
	};

	enum class ForceType {
		FORCE = 0,
		IMPULSE
	};

	struct PhysicsObjectData {
		glm::vec2 Position = { 0.0f, 0.0f };
		float Rotation = 0.0f;
		float Mass = 1.0f;
		bool FixedRotation = false;
		BodyType Type = BodyType::DYNAMIC;
	};
}