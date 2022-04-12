#pragma once
#include "Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SE {
	class Transform2D : public Component {
	public:
		Transform2D() = default;
		Transform2D(const glm::vec2& origin)
			: Position(origin) {
		}

		void Move(const glm::vec2& delta) {
			Position += delta;
		}

		void Rotate(float delta) {
			Rotation -= delta;
		}

		const glm::mat4& GetTransform() const { return m_Transform; }
		const glm::mat4& UpdateTransform() {
			m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, 0.0f))
				* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 0.0f, -1.0f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(Scale.x, Scale.y, 1.0f));

			return m_Transform;
		}

		static const char* GetName() { return "Transform"; }

	public:
		glm::vec2 Position = { 0.0f, 0.0f };
		glm::vec2 Scale = { 1.0f, 1.0f };
		float Rotation = 0.0f;

	private:
		glm::mat4 m_Transform = glm::mat4(1.0f);
	};
}