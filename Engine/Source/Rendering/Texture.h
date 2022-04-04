#pragma once
#include "IBindable.h"

#include <string>

namespace SE {
	struct TextureCreateInfo {
		uint32_t DataType;
		uint32_t Format;
		uint32_t InternalFormat;
		uint32_t Width;
		uint32_t Height;
		uint32_t MinFilter;
		uint32_t MagFilter;
		uint32_t WrapModeR;
		uint32_t WrapModeS;
		uint32_t WrapModeT;

		uint8_t* PixelData;
		bool GenerateMips;
	};

	class Texture : public IBindable {
	public:
		Texture() = default;
		virtual ~Texture() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		uint32_t GetHandle() const {
			return m_Handle;
		}
	};

	class Texture2D : public Texture {
	public:
		static std::shared_ptr<Texture2D> Create(const std::string& filepath);
		static std::shared_ptr<Texture2D> Create(const TextureCreateInfo& createInfo);

		Texture2D(const std::string& filepath);
		Texture2D(const TextureCreateInfo& createInfo);
		~Texture2D();

		void Bind() override;
		void Unbind() override;

		void SetBindingUnit(uint32_t unit);
		void Recreate(const TextureCreateInfo& createInfo);

	private:
		uint32_t m_BindingUnit = 0;
	};
}