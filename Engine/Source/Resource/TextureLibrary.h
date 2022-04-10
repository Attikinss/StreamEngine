#pragma once
#include "Rendering/Texture.h"
#include <unordered_map>

namespace SE {
	class TextureLibrary {
		friend class Renderer;
	public:
		TextureLibrary() = default;
		~TextureLibrary() = default;

		void Initialize();
		void Shutdown();

		const std::shared_ptr<Texture2D>& GetTexture(uint8_t handle) const {
			return m_Textures.at(handle);
		}

		uint8_t CreateTexture(const std::string& filepath);
		void DestroyTexture(uint8_t handle);

	private:
		std::unordered_map<uint8_t, std::shared_ptr<Texture2D>> m_Textures;
		std::vector<uint8_t> m_Handles;
	};
}