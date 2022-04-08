#include "StreamEnginePCH.h"
#include "TextureLibrary.h"

#include "Utilities/File.h"

namespace SE {
	static bool CompareStrings(const char* str, const char** compArr, int32_t count) {
		for (int32_t i = 0; i < count; i++) {
			if (strcmp(str, compArr[i]) == 0) {
				return true;
			}
		}
		
		return false;
	}

	void TextureLibrary::Initialize() {
		// .tga, .png, jpg/jpeg, .psd;
		static const char* supportedExtensions[] = { "png", "tga", "jpg" };
		static const char* textureFilepath = "Assets/Textures/";
		
		// Iterate through folder location for all valid extension types
		for (auto path : File::GetFilesAtDirectory(textureFilepath)) {
			std::string extension = path.substr(path.find_last_of('.') + 1);

			if (!CompareStrings(extension.c_str(), supportedExtensions, 3)) {
				continue;
			}

			// Add texture if created successfully
			auto texture = Texture2D::Create(path);
			if (texture->CreatedSuccessfully()) {
				std::string filename = path.substr(path.find_last_of('/') + 1);
				m_Textures[filename] = texture;
			}
		}

		Logger::Trace("Texture Library Initialized...");
	}

	void TextureLibrary::Shutdown() {
		m_Textures.clear();

		Logger::Trace("Texture Library Shutdown...");
	}
}