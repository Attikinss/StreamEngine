#pragma once
#include "TextureLibrary.h"

namespace SE {
	class ResourceManager {
	public:
		static ResourceManager& Get();

		const TextureLibrary& GetTextureLibrary() const { return m_TextureLibrary; }

		void Initialize();
		void Shutdown();

	private:
		TextureLibrary m_TextureLibrary;
	};
}