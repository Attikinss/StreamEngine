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
		SpriteRenderer(const std::shared_ptr<Texture2D>& texture, const std::shared_ptr<Material>& material)
			: Texture(texture), Material(material) {
		}

		void SetTexture(const std::shared_ptr<Texture2D>& texture) { Texture = texture; }
		void SetMaterial(const std::shared_ptr<Material>& material) { Material = material; }

		static const char* GetName() { return "SpriteRenderer"; }

	public:
		glm::vec4 Color = glm::vec4(1.0f);

		bool FlipX = false;
		bool FlipY = false;

	private:
		std::shared_ptr<Texture2D> Texture;
		std::shared_ptr<Material> Material;
	};
}