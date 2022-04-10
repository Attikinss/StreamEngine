#pragma once
#include "Rendering/Material.h"
#include "Rendering/Texture.h"

#include "Component.h"

#include <glm/glm.hpp>

namespace SE {
	class SpriteRenderer : public Component {
		friend class Renderer;

	public:
		SpriteRenderer() = default;
		SpriteRenderer(uint8_t textureHandle, const std::shared_ptr<Material>& material)
			: m_TextureHandle(textureHandle), m_Material(material) {
		}

		void SetTexture(uint8_t textureHandle) { m_TextureHandle = textureHandle; }
		void SetMaterial(const std::shared_ptr<Material>& material) { m_Material = material; }

		static const char* GetName() { return "SpriteRenderer"; }

	public:
		glm::vec4 Color = glm::vec4(1.0f);

		bool FlipX = false;
		bool FlipY = false;

	private:
		uint8_t m_TextureHandle = 0;
		std::shared_ptr<Material> m_Material;
	};
}