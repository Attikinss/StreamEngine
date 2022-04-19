#pragma once
#include "Rendering/Material.h"
#include "Rendering/Texture.h"

#include "Component.h"

#include <glm/glm.hpp>

namespace SE {
	class SpriteRenderer : public Component {
		friend class SpriteAnimator;
		friend class Renderer;

	public:
		SpriteRenderer() = default;
		SpriteRenderer(std::shared_ptr<Texture2D> texture, const std::shared_ptr<Material>& material)
			: m_Texture(texture), m_Material(material) {
		}

		void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; }
		void SetMaterial(const std::shared_ptr<Material>& material) { m_Material = material; }

		static const char* GetName() { return "SpriteRenderer"; }

	public:
		glm::vec4 Color = glm::vec4(1.0f);

		bool FlipX = false;
		bool FlipY = false;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<Material> m_Material;
	};
}