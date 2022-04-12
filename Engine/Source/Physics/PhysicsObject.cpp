#include "StreamEnginePCH.h"
#include "PhysicsObject.h"

#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

namespace SE {
	PhysicsObject::PhysicsObject(b2World* world)
		: m_World(world), m_Body(nullptr) {

	}

	PhysicsObject::~PhysicsObject() {
		m_World->DestroyBody(m_Body);
		m_World = nullptr;
	}

	void PhysicsObject::SetBoxCollision(float density, float friction, float rest, float restThreshold, const glm::vec2& size, const glm::vec2& offset) {
		b2PolygonShape boxShape;
		boxShape.SetAsBox(size.x * 0.5f, size.y * 0.5f, { offset.x, offset.y }, 0.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = rest;
		fixtureDef.restitutionThreshold = restThreshold;
		m_Body->CreateFixture(&fixtureDef);
	}

	void PhysicsObject::SetCircleCollision(float density, float friction, float rest, float restThreshold, float radius, const glm::vec2& offset) {
		b2CircleShape circleShape;
		circleShape.m_radius = radius;
		circleShape.m_p.Set(offset.x, offset.y);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = rest;
		fixtureDef.restitutionThreshold = restThreshold;
		m_Body->CreateFixture(&fixtureDef);
	}

	void PhysicsObject::SetBodyType(BodyType type) {
		b2BodyType b2Type;
		switch (type) {
			case SE::BodyType::DYNAMIC:
				b2Type = b2BodyType::b2_dynamicBody;
				break;
			case SE::BodyType::KINEMATIC:
				b2Type = b2BodyType::b2_kinematicBody;
				break;
			case SE::BodyType::STATIC:
			default:
				b2Type = b2BodyType::b2_staticBody;
				break;
		}

		m_Body->SetType(b2Type);
		if (b2Type == b2BodyType::b2_dynamicBody) {
			m_Body->SetAwake(true);
		}
	}

	glm::vec2 PhysicsObject::GetPosition() {
		b2Vec2 position = m_Body->GetPosition();
		return { position.x, position.y };
	}

	float PhysicsObject::GetRotation() {
		return -glm::degrees(m_Body->GetAngle());
	}
}