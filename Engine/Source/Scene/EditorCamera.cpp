#include "StreamEnginePCH.h"
#include "EditorCamera.h"

#include "Core/Input.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

#include <glm/gtc/matrix_transform.hpp>

namespace SE {
	EditorCamera::EditorCamera(const glm::vec2& viewSize, const glm::vec2& position, float rotation)
		: m_Position(position), m_Rotation(rotation), Camera(viewSize) {
	}

	EditorCamera::EditorCamera(float viewX, float viewY, const glm::vec2& position, float rotation)
		: m_Position(position), m_Rotation(rotation), Camera(viewX, viewY) {
	}

	void EditorCamera::OnUpdate() {
		glm::vec2 delta = Input::GetMouseDelta() * 0.5f;

		bool leftAltPressed = Input::GetKey(Key::LEFT_ALT);
		bool leftMouseBtnPressed = Input::GetMouseButton(Button::BUTTON_LEFT);
		bool rightMouseBtnPressed = Input::GetMouseButton(Button::BUTTON_RIGHT);
		bool middleMouseBtnPressed = Input::GetMouseButton(Button::BUTTON_MIDDLE);

		if (leftAltPressed) {
			if (leftMouseBtnPressed) {
				Pan(delta * 0.01f);
			}
			else if (rightMouseBtnPressed) {
				Zoom(delta.y * 0.01f);
			}
		}
		else if (middleMouseBtnPressed) {
			Pan(delta * 0.01f);
		}

		if (m_IsDirty) {
			RecalculateProjection();
			RecalculateView();
		}
	}

	void EditorCamera::OnEvent(Event& evt) {
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_FUNCTION(EditorCamera::OnMouseScroll));
	}

	void EditorCamera::Pan(const glm::vec2& delta) {
		const glm::vec2 d(delta.x * -1.0f, delta.y);

		m_Position += d * m_Zoom * 0.5f;
		m_IsDirty = true;
	}

	void EditorCamera::Zoom(float delta) {
		m_Zoom += delta;
		if (m_Zoom < 0.01f) {
			m_Zoom = 0.01f;
		}
		if (m_Zoom > 100.0f) {
			m_Zoom = 100.0f;
		}

		m_IsDirty = true;
	}

	void EditorCamera::RecalculateView() {
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f))
					 * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(m_ViewMatrix);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_IsDirty = false;
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& evt) {
		float delta = evt.GetOffset().second * m_Zoom * -0.1f;
		Zoom(delta);

		return false;
	}

}