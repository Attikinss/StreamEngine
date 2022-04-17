#pragma once
#include "IBindable.h"

#include <string>

namespace SE {
	struct TextureCreateInfo {
		uint32_t DataType = 5121;
		uint32_t Format = 6408;
		uint32_t InternalFormat = 32856;
		uint32_t Width = 1;
		uint32_t Height = 1;
		uint32_t MinFilter = 9729;
		uint32_t MagFilter = 9729;
		uint32_t WrapModeR = 10497;
		uint32_t WrapModeS = 10497;
		uint32_t WrapModeT = 10497;

		uint8_t* PixelData = nullptr;
		bool GenerateMips = false;
	};

	class Texture : public IBindable {
	public:
		Texture() = default;
		virtual ~Texture() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

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

		void Bind() const override;
		void Unbind() const override;

		void SetBindingUnit(uint32_t unit);
		void Recreate(const TextureCreateInfo& createInfo);

		bool CreatedSuccessfully() const { return m_CreationSuccessful; }

	private:
		uint32_t m_BindingUnit = 0;
		bool m_CreationSuccessful = false;
	};
}