#pragma once
#include "IBindable.h"
#include "Texture.h"

#include <vector>

namespace SE {
	enum class FramebufferTextureFormat {
		NONE = 0,
		RGBA8,
		DEPTH24_STENCIL8,
	};

	struct FramebufferCreateInfo {
		uint32_t Width, Height;
		std::vector<FramebufferTextureFormat> TextureFormats;

		FramebufferCreateInfo() = default;
		FramebufferCreateInfo(uint32_t width, uint32_t height, std::initializer_list<FramebufferTextureFormat> formats)
			: Width(width), Height(height), TextureFormats(formats) {
		}
	};

	class Framebuffer : public IBindable {
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferCreateInfo& createInfo);

		Framebuffer(const FramebufferCreateInfo& createInfo);
		~Framebuffer();

		void Bind() const override;
		void Unbind() const override;
		void BindTexture(uint32_t index, uint32_t unit = 0) const;

		void Recreate(uint32_t width, uint32_t height, bool forceCreate = false);

		std::pair<uint32_t, uint32_t> GetSize() const;
		const Texture2D& GetColourAttachment(uint32_t index = 0) const;

	private:
		uint32_t m_Width, m_Height;

		std::vector<FramebufferTextureFormat> m_ColorAttachmentFormats;
		FramebufferTextureFormat m_DepthAttachmentFormat = FramebufferTextureFormat::NONE;

		std::vector<Texture2D*> m_ColorAttachments;
		Texture2D* m_DepthAttachment = nullptr;
	};
}