#include "StreamEnginePCH.h"
#include "PhysicsScene.h"

#include <box2d/b2_body.h>
#include <box2d/b2_world.h>

namespace SE {
	static b2BodyType BodyTypeTob2BodyType(BodyType type) {
		switch (type) {
			case SE::BodyType::DYNAMIC:		return b2BodyType::b2_dynamicBody;
			case SE::BodyType::KINEMATIC:	return b2BodyType::b2_kinematicBody;
			case SE::BodyType::STATIC:		return b2BodyType::b2_staticBody;
			default:						return b2BodyType::b2_staticBody;
		}
	}

	PhysicsScene::PhysicsScene(const glm::vec2& gravity)
		: m_World(new b2World({ gravity.x, gravity.y })) {
	}

	PhysicsScene::~PhysicsScene() {
		delete m_World;
	}

	PhysicsObject* PhysicsScene::CreatePhysicsObject(PhysicsObjectData data) {
		PhysicsObject* physObj = new PhysicsObject(m_World);

		b2BodyDef bodyDef;
		bodyDef.position = { data.Position.x, data.Position.y };
		bodyDef.angle = glm::radians(-data.Rotation);
		bodyDef.fixedRotation = data.FixedRotation;
		bodyDef.type = BodyTypeTob2BodyType(data.Type);

		b2MassData massData;
		massData.mass = data.Mass;

		physObj->m_Body = m_World->CreateBody(&bodyDef);
		physObj->m_Body->SetMassData(&massData);
		physObj->m_World = m_World;

		return physObj;
	}

	void PhysicsScene::Step() {
		const static float timeStep = 1.0f / 60.0f;
		m_World->Step(timeStep, 10, 8);
	}

	void PhysicsScene::SetGravity(const glm::vec2& gravity) {
		m_World->SetGravity({ gravity.x, gravity.y });
	}

	glm::vec2 PhysicsScene::GetGravity() const {
		b2Vec2 gravity = m_World->GetGravity();
		return { gravity.x, gravity.y };
	}

}