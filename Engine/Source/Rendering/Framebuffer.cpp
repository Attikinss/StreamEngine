#include "StreamEnginePCH.h"
#include "Framebuffer.h"
#include "Core/Application.h"

#include <glad/gl.h>

namespace SE {
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferCreateInfo& createInfo) {
		return std::make_shared<Framebuffer>(createInfo);
	}

	Framebuffer::Framebuffer(const FramebufferCreateInfo& createInfo)
		: m_Width(createInfo.Width), m_Height(createInfo.Height) {
		for (const auto& format : createInfo.TextureFormats) {
			// Specify info about desired attachments
			switch (format) {
				case FramebufferTextureFormat::RGBA8:
					m_ColorAttachmentFormats.emplace_back(format);
					break;
				case FramebufferTextureFormat::DEPTH24_STENCIL8:
					m_DepthAttachmentFormat = format;
					break;

				case FramebufferTextureFormat::NONE:
				default:
					break;
			}
		}

		if (createInfo.Width == 0 || createInfo.Height == 0) {
			auto[x, y] = Application::Get().GetWindow().GetSize();
			Recreate(x, y, true);
		}
		else {
			Recreate(createInfo.Width, createInfo.Height, true);
		}
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &m_Handle);

		for (uint32_t i = 0; i < m_ColorAttachments.size(); i++) {
			delete m_ColorAttachments[i];
		}

		delete m_DepthAttachment;
	}

	void Framebuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::BindTexture(uint32_t index, uint32_t unit) const {
		_ASSERT(index < m_ColorAttachments.size());

		m_ColorAttachments[index]->SetBindingUnit(unit);
		m_ColorAttachments[index]->Bind();
	}

	void Framebuffer::Recreate(uint32_t width, uint32_t height, bool forceCreate) {
		// Ensure recreation only happens if there is a change and if the window is not minimized
		if ((!forceCreate && width == m_Width && height == m_Height) || (width <= 0 || height <= 0)) {
			return;
		}

		m_Width = width;
		m_Height = height;

		if (m_Handle) {
			glDeleteFramebuffers(1, &m_Handle);

			glCreateFramebuffers(1, &m_Handle);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

			for (uint32_t i = 0; i < m_ColorAttachments.size(); i++) {
				TextureCreateInfo createInfo;
				createInfo.PixelData = nullptr;
				createInfo.DataType = GL_UNSIGNED_BYTE;
				createInfo.Format = GL_RGBA;
				createInfo.InternalFormat = GL_RGBA8;
				createInfo.Width = width;
				createInfo.Height = height;
				createInfo.MinFilter = GL_LINEAR;
				createInfo.MagFilter = GL_LINEAR;
				createInfo.WrapModeR = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeS = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeT = GL_CLAMP_TO_EDGE;
				createInfo.GenerateMips = false;

				m_ColorAttachments[i]->Recreate(createInfo);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachments[i]->GetHandle(), 0);
			}

			if (m_DepthAttachment) {
				TextureCreateInfo createInfo;
				createInfo.PixelData = nullptr;
				createInfo.DataType = GL_UNSIGNED_INT_24_8;
				createInfo.Format = GL_DEPTH_STENCIL;
				createInfo.InternalFormat = GL_DEPTH24_STENCIL8;
				createInfo.Width = width;
				createInfo.Height = height;
				createInfo.MinFilter = GL_LINEAR;
				createInfo.MagFilter = GL_LINEAR;
				createInfo.WrapModeR = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeS = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeT = GL_CLAMP_TO_EDGE;
				createInfo.GenerateMips = false;

				m_DepthAttachment->Recreate(createInfo);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment->GetHandle(), 0);
			}
		}
		else {
			glCreateFramebuffers(1, &m_Handle);
			glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

			// Create framebuffer color attachment(s)
			if (m_ColorAttachmentFormats.size() > 0) {
				m_ColorAttachments.resize(m_ColorAttachmentFormats.size());

				for (uint32_t i = 0; i < m_ColorAttachmentFormats.size(); i++) {
					TextureCreateInfo createInfo;
					createInfo.PixelData = nullptr;
					createInfo.DataType = GL_UNSIGNED_BYTE;
					createInfo.Format = GL_RGBA;
					createInfo.InternalFormat = GL_RGBA8;
					createInfo.Width = width;
					createInfo.Height = height;
					createInfo.MinFilter = GL_LINEAR;
					createInfo.MagFilter = GL_LINEAR;
					createInfo.WrapModeR = GL_CLAMP_TO_EDGE;
					createInfo.WrapModeS = GL_CLAMP_TO_EDGE;
					createInfo.WrapModeT = GL_CLAMP_TO_EDGE;
					createInfo.GenerateMips = false;

					Texture2D* newTex = new Texture2D(createInfo);
					newTex->Bind();

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, newTex->GetHandle(), 0);
					m_ColorAttachments[i] = newTex;
				}
			}

			// Create framebuffer depth attachment
			if (m_DepthAttachmentFormat != FramebufferTextureFormat::NONE) {
				TextureCreateInfo createInfo;
				createInfo.PixelData = nullptr;
				createInfo.DataType = GL_UNSIGNED_INT_24_8;
				createInfo.Format = GL_DEPTH_STENCIL;
				createInfo.InternalFormat = GL_DEPTH24_STENCIL8;
				createInfo.Width = width;
				createInfo.Height = height;
				createInfo.MinFilter = GL_LINEAR;
				createInfo.MagFilter = GL_LINEAR;
				createInfo.WrapModeR = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeS = GL_CLAMP_TO_EDGE;
				createInfo.WrapModeT = GL_CLAMP_TO_EDGE;
				createInfo.GenerateMips = false;

				Texture2D* newTex = new Texture2D(createInfo);
				newTex->Bind();

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, newTex->GetHandle(), 0);
				m_DepthAttachment = newTex;
				m_DepthAttachment->Unbind();
			}
		}

		if (m_ColorAttachments.size() > 1) {
			// TODO: Assert here if too many colour attachments
			//		 (Figure out how many is too many...)

			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((uint32_t)m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
			glDrawBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Logger::Error("Framebuffer failed to complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	std::pair<uint32_t, uint32_t> Framebuffer::GetSize() const {
		return { m_Width, m_Height };
	}

	const Texture2D& Framebuffer::GetColourAttachment(uint32_t index) const {
		_ASSERT(index < m_ColourAttachments.size());

		return *m_ColorAttachments[index];
	}
}