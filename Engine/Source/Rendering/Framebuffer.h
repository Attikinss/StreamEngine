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

	struct FramebufferTextureInfo {
		FramebufferTextureFormat Format;

		FramebufferTextureInfo() = default;
		FramebufferTextureInfo(FramebufferTextureFormat format)
			: Format(format) {
		}
	};

	struct FramebufferAttachmentInfo {
		std::vector<FramebufferTextureInfo> Textures;

		FramebufferAttachmentInfo() = default;
		FramebufferAttachmentInfo(std::initializer_list<FramebufferTextureInfo> textures)
			: Textures(textures) {
		}
	};

	struct FramebufferCreateInfo {
		uint32_t Width, Height;
		FramebufferAttachmentInfo Attachments;
	};

	class Framebuffer : public IBindable {
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferCreateInfo& createInfo);

		Framebuffer(const FramebufferCreateInfo& createInfo);
		~Framebuffer();

		void Bind() override;
		void Unbind() override;
		void BindTexture(uint32_t index) const;

		void Recreate(uint32_t width, uint32_t height, bool forceCreate = false);

		std::pair<uint32_t, uint32_t> GetSize() const;
		const Texture2D* GetColourAttachment(uint32_t index = 0) const;

	private:
		uint32_t m_Width, m_Height;

		std::vector<FramebufferTextureFormat> m_ColorAttachmentFormats;
		FramebufferTextureFormat m_DepthAttachmentFormat = FramebufferTextureFormat::NONE;

		std::vector<Texture2D*> m_ColorAttachments;
		Texture2D* m_DepthAttachment = nullptr;
	};
}