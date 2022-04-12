#include "StreamEnginePCH.h"
#include "Rigidbody2D.h"

#include "Physics/PhysicsObject.h"

namespace SE {
	void Rigidbody2D::ApplyForce(const glm::vec2& force, ForceType type) {
		m_PhysObject->ApplyForce(force, type);
	}

	void Rigidbody2D::ApplyForceToPoint(const glm::vec2& force, const glm::vec2& point, ForceType type) {
		m_PhysObject->ApplyForceToPoint(force, point, type);
	}

	void Rigidbody2D::ApplyTorque(float torque) {
		m_PhysObject->ApplyTorque(-torque);
	}

	void Rigidbody2D::SetPosition(const glm::vec2& position) {
		m_PhysObject->SetPosition(position);
	}

	void Rigidbody2D::SetRotation(float rotation) {
		m_PhysObject->SetRotation(rotation);
	}

	void Rigidbody2D::Move(const glm::vec2& delta) {
		m_PhysObject->SetPosition(m_PhysObject->GetPosition() + delta);
	}

	void Rigidbody2D::Rotate(float delta) {
		m_PhysObject->SetRotation(m_PhysObject->GetRotation() + delta);
	}
}