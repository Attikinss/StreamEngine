#pragma once
#include "SpriteRenderer.h"

namespace SE {
	enum class PlaybackType {
		ONCE = 0,
		LOOP,
		PING_PONG
	};

	class SpriteAnimator : public Component {
		friend class Scene;

	public:
		SpriteAnimator() = default;

		void SetFrameCount(uint32_t perRow, uint32_t perColumn) {
			FramesPerRow = perRow;
			FramesPerColumn = perColumn;
			MaxFrames = perRow * perColumn;
		}

		void SetFrameCount(uint32_t perRow, uint32_t perColumn, uint32_t maxFrames) {
			FramesPerRow = perRow;
			FramesPerColumn = perColumn;
			MaxFrames = maxFrames;
		}

		void SetFrameSize(uint32_t width, uint32_t height) {
			FrameWidth = width;
			FrameHeight = height;
		}

		void SetFrameSizeAuto() {
			auto [width, height] = m_Texture->GetSize();
			FrameWidth = width / FramesPerRow;
			FrameHeight = height / FramesPerColumn;
		}

		void SetTexture(const std::shared_ptr<Texture2D>& texture) {
			m_Texture = texture;
		}

		std::pair<glm::vec2, glm::vec2> GetFrameCoords() {
			auto[width, height] = m_Texture->GetSize();

			int32_t tileX = ((m_FrameIndex % FramesPerRow) + FramesPerRow) % FramesPerRow;
			int32_t tileY = (m_FrameIndex / FramesPerRow);

			float x = (float)(tileX * FrameWidth) / width;
			float y = (float)(tileY * FrameHeight) / height;

			return { { x, y }, { (float)FrameWidth / width, (float)FrameHeight / height } };
		}

		void NextFrame(float deltaTime) {
			if (!Animate) {
				return;
			}

			if (IsComplete) {
				switch (Playback) {
					case SE::PlaybackType::LOOP:
						IsComplete = false;
						m_FrameIndex = 0;
						break;

					// TODO: Implement ping pong
					case SE::PlaybackType::ONCE:
					case SE::PlaybackType::PING_PONG:
					default: return;
				}
			}

			m_CurrentTime -= deltaTime;
			if (m_CurrentTime <= 0.0f) {
				m_CurrentTime = 1.0f / AnimationSpeed;

				if (++m_FrameIndex >= (int32_t)MaxFrames) {
					IsComplete = true;
					m_FrameIndex = MaxFrames;
				}
			}
		}

		static const char* GetName() { return "SpriteAnimator"; }

	public:
		PlaybackType Playback = PlaybackType::ONCE;
		uint32_t FrameWidth = 0;
		uint32_t FrameHeight = 0;

		uint32_t FramesPerRow = 1;
		uint32_t FramesPerColumn = 1;
		uint32_t MaxFrames = 1;

		// NOTE: This is just an arbitrary number until a FPS can be properly measured
		float AnimationSpeed = 50.0f;
		bool Animate = true;
		bool IsComplete = false;

	private:
		int32_t m_FrameIndex= 0;
		float m_CurrentTime = 0.0f;
		std::shared_ptr<Texture2D> m_Texture;
	};
}