#pragma once
#include "Rendering/Camera.h"
#include <glm/glm.hpp>

namespace SE {
	class Event;
	class MouseScrolledEvent;

	class EditorCamera : public Camera {
	public:
		EditorCamera(const glm::vec2& viewSize, const glm::vec2& position = { 0.0f, 0.0f }, float rotation = 0.0f);
		EditorCamera(float viewX, float viewY, const glm::vec2& position = { 0.0f, 0.0f }, float rotation = 0.0f);

		void OnUpdate();
		void OnEvent(Event& evt);

	private:
		void Pan(const glm::vec2& delta);
		void Zoom(float delta);
		void RecalculateView();

		bool OnMouseScroll(MouseScrolledEvent& evt);

	private:
		glm::vec2 m_Position = { 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		bool m_IsDirty = false;
	};
}