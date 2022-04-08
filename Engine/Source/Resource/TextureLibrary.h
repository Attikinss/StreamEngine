#pragma once
#include "Rendering/Texture.h"
#include <unordered_map>

namespace SE {
	class TextureLibrary {
	public:
		TextureLibrary() = default;
		~TextureLibrary() = default;

		void Initialize();
		void Shutdown();

		const std::shared_ptr<Texture2D>& GetTexture(const std::string& name) const {
			return m_Textures.at(name);
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;
	};
}