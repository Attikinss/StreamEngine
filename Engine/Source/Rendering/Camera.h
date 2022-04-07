#pragma once
#include <glm/glm.hpp>

namespace SE {
	class Camera {
	public:
		Camera() = default;
		Camera(float xSize, float ySize);
		Camera(const glm::vec2& viewSize);

		void SetViewSize(const glm::vec2& viewSize);
		void SetView(const glm::mat4& viewMat);
		void SetZoom(float zoom);

		const glm::mat4& GetView() const;
		const glm::mat4& GetProjection() const;
		const glm::mat4& GetViewProjection() const;

	protected:
		void RecalculateProjection();

	protected:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

		glm::vec2 m_ViewSize = glm::vec2(0.0f);
		float m_Zoom = 1.0f;
	};
}