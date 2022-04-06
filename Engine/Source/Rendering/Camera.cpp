#include "Camera.h"
#include "Core/Logger.h"

#include <glm/gtc/matrix_transform.hpp>

namespace SE {
    Camera::Camera(float xSize, float ySize)
        : Camera(glm::vec2(xSize, ySize)) {

    }

    Camera::Camera(const glm::vec2& viewSize)
    : m_ViewSize(viewSize) {
        RecalculateProjection();
    }

    void Camera::SetViewSize(const glm::vec2& viewSize) {
        if (viewSize == m_ViewSize) {
            return;
        }

        m_ViewSize = viewSize;
        RecalculateProjection();
    }

    void Camera::SetView(const glm::mat4& viewMat) {
        m_ViewMatrix = viewMat;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera::SetZoom(float zoom) {
        if (m_Zoom == zoom) {
            return;
        }

        m_Zoom = zoom;
        RecalculateProjection();
    }

    const glm::mat4& Camera::GetView() const {
        return m_ViewMatrix;
    }

    const glm::mat4& Camera::GetProjection() const {
        return m_ProjectionMatrix;
    }

    const glm::mat4& Camera::GetViewProjection() const {
        return m_ViewProjectionMatrix;
    }

    void Camera::RecalculateProjection() {
        float aspectRatio = m_ViewSize.x / m_ViewSize.y;
        m_ProjectionMatrix = glm::ortho(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}