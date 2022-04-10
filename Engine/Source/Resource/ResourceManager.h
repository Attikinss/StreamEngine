#pragma once
#include "TextureLibrary.h"

namespace SE {
	class ResourceManager {
	public:
		static ResourceManager& Get();

		TextureLibrary& GetTextureLibrary() { return m_TextureLibrary; }

		void Initialize();
		void Shutdown();

	private:
		TextureLibrary m_TextureLibrary;
	};
}