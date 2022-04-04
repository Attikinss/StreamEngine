#include "Texture.h"

#include "Core/Logger.h"
#include "StbImage/stb_image.h"

#include <glad/gl.h>

namespace SE {
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath) {
		return std::make_shared<Texture2D>(filepath);
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

		int32_t width, height, channelCount;
		uint8_t* pixelData = stbi_load(filepath.c_str(), &width, &height, &channelCount, 0);

		if (pixelData) {
			TextureCreateInfo createInfo;
			createInfo.DataType = GL_UNSIGNED_BYTE;
			createInfo.PixelData = pixelData;
			createInfo.Width = width;
			createInfo.Height = height;
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

			// Create texture/image
			CreateTexture(createInfo);
		}
		else {
			Logger::Error("Failed to load texture: Invalid file!");
		}

		// Free the memory of the image currently loaded
		stbi_image_free(pixelData);
	}

	Texture2D::Texture2D(const TextureCreateInfo& createInfo) {
		CreateTexture(createInfo);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_Handle);
	}

	void Texture2D::Bind() {
		glBindTextureUnit(m_BindingUnit, m_Handle);
	}

	void Texture2D::Unbind() {
		// TODO: Figure out if this causes issues internally
		glBindTextureUnit(m_BindingUnit, 0);
	}

	void Texture2D::SetBindingUnit(uint32_t unit) {
		m_BindingUnit = unit;
	}

	void Texture2D::CreateTexture(const TextureCreateInfo& createInfo) {
		// Create and bind texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Handle);
		SetBindingUnit(0);
		Bind();

		// Specify how texture is stored
		glTextureStorage2D(m_Handle, 1, createInfo.InternalFormat, createInfo.Width, createInfo.Height);

		// Setup texture filtering
		glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, createInfo.MinFilter);
		glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, createInfo.MagFilter);

		// Setup texture wrapping
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_R, createInfo.WrapModeR);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_S, createInfo.WrapModeS);
		glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_T, createInfo.WrapModeT);

		// Specify texture format and data to be written
		glTextureSubImage2D(m_Handle, 0, 0, 0, createInfo.Width, createInfo.Height, createInfo.Format, createInfo.DataType, createInfo.PixelData);
		
		if (createInfo.GenerateMips) {
			glGenerateTextureMipmap(m_Handle);
		}

		Unbind();
	}
}