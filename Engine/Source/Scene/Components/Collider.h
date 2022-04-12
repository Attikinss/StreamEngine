#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace SE {
	class PhysicsObject;

	class Collider : public Component {
	public:
		virtual ~Collider() = default;

	public:
		glm::vec2 Offset = { 0.0f, 0.0f };
		float Density = 1.0f;
		float Friction = 0.25f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;
	};

	class BoxCollider2D : public Collider {
		friend class Scene;

	public:
		BoxCollider2D() = default;
		~BoxCollider2D() = default;

		static const char* GetName() { return "BoxCollider2D"; }

	public:
		glm::vec2 Size = { 1.0f, 1.0f };
	};

	class CircleCollider : public Collider {
		friend class Scene;
		
	public:
		CircleCollider() = default;
		~CircleCollider() = default;

		static const char* GetName() { return "CircleCollider"; }

	public:
		float Radius = 0.5f;
	};
}