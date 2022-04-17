#include "StreamEnginePCH.h"
#include "Texture.h"

#include "StbImage/stb_image.h"

#include <glad/gl.h>

namespace SE {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath) {
		return std::make_shared<Texture2D>(filepath);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		TextureCreateInfo createInfo;
		createInfo.Width = width;
		createInfo.Height = height;
		return std::make_shared<Texture2D>(createInfo);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const TextureCreateInfo& createInfo) {
		return std::make_shared<Texture2D>(createInfo);
	}

	Texture2D::Texture2D(const std::string& filepath) {
		if (filepath.empty()) {
			Logger::Error("Failed to load texture - No filepath specified!");
			_ASSERT(false);
		}

		stbi_set_flip_vertically_on_load(true);

		int32_t channelCount;
		uint8_t* pixelData = stbi_load(filepath.c_str(), &m_Width, &m_Height, &channelCount, 0);

		if (pixelData) {
			TextureCreateInfo createInfo;
			createInfo.DataType = GL_UNSIGNED_BYTE;
			createInfo.PixelData = pixelData;
			createInfo.Width = m_Width;
			createInfo.Height = m_Height;
			createInfo.WrapModeR = GL_REPEAT;
			createInfo.WrapModeS = GL_REPEAT;
			createInfo.WrapModeT = GL_REPEAT;
			createInfo.MinFilter = GL_LINEAR;
			createInfo.MagFilter = GL_NEAREST;
			createInfo.GenerateMips = true;

			if (channelCount == 1) {
				createInfo.Format = GL_RED;
				createInfo.InternalFormat = GL_R8;
			}
			else if (channelCount == 2) {
				createInfo.Format = GL_RG;
				createInfo.InternalFormat = GL_RG8;
			}
			else if (channelCount == 3) {
				createInfo.Format = GL_RGB;
				createInfo.InternalFormat = GL_RGB8;
			}
			else if (channelCount == 4) {
				createInfo.Format = GL_RGBA;
				createInfo.InternalFormat = GL_RGBA8;
			}

			m_DataFormat = createInfo.Format;

			// Create texture/image
			Recreate(createInfo);
			m_CreationSuccessful = true;
		}
		else {
			Logger::Error("Failed to load texture: Invalid file!");
		}

		// Free the memory of the image currently loaded
		stbi_image_free(pixelData);
	}

	Texture2D::Texture2D(const TextureCreateInfo& createInfo) {
		Recreate(createInfo);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_Handle);
	}

	void Texture2D::Bind() const {
		glBindTextureUnit(m_BindingUnit, m_Handle);
	}

	void Texture2D::Unbind() const {
		glBindTextureUnit(m_BindingUnit, 0);
	}

	void Texture2D::SetData(uint32_t size, void* data) {
		glTextureSubImage2D(m_Handle, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::SetPixel(uint32_t x, uint32_t y, void* data) {
		glTextureSubImage2D(m_Handle, 0, x, y, 1, 1, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::SetBindingUnit(uint32_t unit) {
		m_BindingUnit = unit;
	}

	void Texture2D::Recreate(const TextureCreateInfo& createInfo) {
		m_Width = createInfo.Width;
		m_Height = createInfo.Height;
		m_DataFormat = createInfo.Format;
		
		if (m_Handle) {
			glDeleteTextures(1, &m_Handle);
		}

		// Create and bind texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);

		// Setup texture filtering
		glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, createInfo.MinFilter);
		glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, createInfo.MagFilter);

		// Setup texture wrapping
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_R, createInfo.WrapModeR);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_S, createInfo.WrapModeS);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_T, createInfo.WrapModeT);

		if (createInfo.PixelData) {
			// Specify how texture is stored
			glTextureStorage2D(m_Handle, 1, createInfo.InternalFormat, createInfo.Width, createInfo.Height);

			// Specify texture format and data to be written
			glTextureSubImage2D(m_Handle, 0, 0, 0, createInfo.Width, createInfo.Height, createInfo.Format, createInfo.DataType, createInfo.PixelData);
		}
		else {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_Handle);
			glTexImage2D(GL_TEXTURE_2D, 0, createInfo.InternalFormat, createInfo.Width, createInfo.Height, 0, createInfo.Format, createInfo.DataType, createInfo.PixelData);
		}
		
		if (createInfo.GenerateMips) {
			glGenerateTextureMipmap(m_Handle);
		}

		Unbind();
	}
}