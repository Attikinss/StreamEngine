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
		// Assign ids from 1 to 255 - 0 is uninitialized/invalid
		m_Handles.resize(255);
		for (uint32_t i = 1; i <= m_Handles.size(); i++) {
			m_Handles[i] = i;
		}

		// .tga, .png, jpg/jpeg, .psd;
		//static const char* supportedExtensions[] = { "png", "tga", "jpg" };
		//static const char* textureFilepath = "Assets/Textures/";
		//
		//// Iterate through folder location for all valid extension types
		//for (auto path : File::GetFilesAtDirectory(textureFilepath)) {
		//	std::string extension = path.substr(path.find_last_of('.') + 1);
		//
		//	if (!CompareStrings(extension.c_str(), supportedExtensions, 3)) {
		//		continue;
		//	}
		//
		//	// Add texture if created successfully
		//	CreateTexture(path);
		//}

		Logger::Trace("Texture Library Initialized...");
	}

	void TextureLibrary::Shutdown() {
		m_Textures.clear();

		Logger::Trace("Texture Library Shutdown...");
	}

	uint8_t TextureLibrary::CreateTexture(const std::string& filepath) {
		if (m_Handles.empty()) {
			Logger::Error("Texture Library has no texture handles available! Texture creation aborted.");
			return 0;
		}

		auto texture = Texture2D::Create(filepath);
		if (texture->CreatedSuccessfully()) {
			//std::string filename = path.substr(path.find_last_of('/') + 1);

			uint8_t handle = *m_Handles.erase(m_Handles.begin());
			m_Textures[handle] = texture;
			return handle;
		}

		return 0;
	}

	void TextureLibrary::DestroyTexture(uint8_t handle) {
		if (std::find(m_Handles.begin(), m_Handles.end(), handle) == m_Handles.end()) {
			Logger::Error("Handle is invalid/not in use! Texture destruction aborted.");
			return;
		}

		// Erase the texture and return the handle to the available list
		m_Textures.erase(handle);
		m_Handles.insert(std::upper_bound(m_Handles.begin(), m_Handles.end(), handle), handle);
	}
}