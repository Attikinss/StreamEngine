#include "StreamEnginePCH.h"
#include "Renderer.h"

#include "Batch.h"
#include "Camera.h"
#include "Framebuffer.h"
#include "Quad.h"
#include "Shader.h"
#include "VertexArray.h"

#include "Scene/Components/SpriteRenderer.h"

#include "Resource/ResourceManager.h"

#include "GLStateManager.h"

namespace SE {
    struct RendererData {
        std::shared_ptr<Shader> FramebufferShader;
        std::shared_ptr<Shader> DefaultShader;
        std::shared_ptr<Texture2D> WhitePixelTexture;

        Batch SpriteBatch;

        glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);

        std::shared_ptr<VertexArray> FramebufferVAO;
        std::shared_ptr<Framebuffer> Framebuffer;

        uint32_t TextureBindIndex = 1;
        std::array<std::shared_ptr<Texture2D>, 32> Textures;

        RendererData() {
            // Create vertex data for framebuffer quad
            float fboVertices[] = {
                -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
                -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
                 1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
                 1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
                 1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
            };

            // Create vbo and vao for framebuffer
            auto fbVBuffer = VertexBuffer::Create(sizeof(fboVertices), fboVertices);
            fbVBuffer->SetLayout({
                { DataType::FLOAT3, "a_Position" },
                { DataType::FLOAT2, "a_UV" }
            });
            FramebufferVAO = VertexArray::Create();
            FramebufferVAO->AddVertexBuffer(fbVBuffer);
            Framebuffer = Framebuffer::Create({ 1280, 720, { FramebufferTextureFormat::RGBA8 } });

            // Create vbo and vao for batching
            SpriteBatch = Batch(UINT16_MAX + 1, sizeof(glm::mat4), {
                { DataType::FLOAT3, "a_Position" },
                { DataType::FLOAT4, "a_Color" },
                { DataType::FLOAT2, "a_UV" },
                { DataType::FLOAT, "a_TextureID" },
                { DataType::MAT4, "a_Transform" }
            });

            // Create shader for framebuffer
            FramebufferShader = Shader::Create({
                "Assets/Shaders/Framebuffer.vert",
                "Assets/Shaders/Framebuffer.frag"
            });
            FramebufferShader->Bind();
            FramebufferShader->SetUniform("u_ColorAttachment", 0);

            // Create default shader for general purpose rendering
            DefaultShader = Shader::Create({
                "Assets/Shaders/Default.vert",
                "Assets/Shaders/Default.frag"
            });

            // Bind all texture samplers for the default shader
            int32_t samplers[32];
            for (int32_t i = 0; i < 32; i++) {
                samplers[i] = i;
            }
            DefaultShader->Bind();
            DefaultShader->SetUniform("u_Textures", samplers, 32);

            // Create default white pixel texture
            uint32_t whitePixel = 0xffffffff;
            WhitePixelTexture = Texture2D::Create(1, 1);
            WhitePixelTexture->SetData(sizeof(uint32_t), &whitePixel);
            Textures[0] = WhitePixelTexture;
        }
    };

    static RendererData* s_RendererData = nullptr;

    bool Renderer::Initialize() {
        Logger::Trace("Renderer Initialised...");

        GLStateManager::InfoDump();
        GLStateManager::EnableDepthTest();
        GLStateManager::EnableBlend();
        GLStateManager::BlendFunc(SrcFactor::SRC_ALPHA, DestFactor::ONE_MINUS_SRC_ALPHA);

        GLStateManager::SetClearColour(0.15f, 0.15f, 0.15f);

        s_RendererData = new RendererData();
        return true;
    }

    bool Renderer::Shutdown() {
        delete s_RendererData;

        Logger::Trace("Renderer Shutdown...");
        return true;
    }

    void Renderer::BeginFrame(const Camera& camera) {
        s_RendererData->Framebuffer->Bind();
        s_RendererData->ViewProjectionMatrix = camera.GetViewProjection();
        s_RendererData->DefaultShader->Bind();
        s_RendererData->DefaultShader->SetUniform("u_ViewProjectionMatrix", s_RendererData->ViewProjectionMatrix);
        //glm::vec3 viewPosition = glm::inverse(camera.GetView())[3];

        GLStateManager::Clear();
    }

    void Renderer::EndFrame() {
        Flush();
        // Bind framebuffer resources
        s_RendererData->Framebuffer->Unbind();
        s_RendererData->Framebuffer->BindTexture(0);
        s_RendererData->FramebufferVAO->Bind();
        s_RendererData->FramebufferVAO->GetVertexBuffers()[0]->Bind();

        s_RendererData->FramebufferShader->Bind();

        // Draw framebuffer quad
        GLStateManager::Clear();
        GLStateManager::DrawArrays(6, 0);
    }

    void Renderer::Submit(const SpriteRenderer& spriteRenderer, const glm::mat4& transform, Quad& quad) {
        // An OpenGL handle value of 0 is invalid
        uint32_t textureID = 0;
        if (spriteRenderer.m_Texture.get() && spriteRenderer.m_Texture->GetHandle() != 0) {
            for (uint32_t i = 0; i < s_RendererData->TextureBindIndex; i++) {
                if (s_RendererData->Textures[i].get() && *spriteRenderer.m_Texture.get() == *s_RendererData->Textures[i].get()) {
                    textureID = i;
                    break;
                }
            }

            if (textureID == 0) {
                s_RendererData->Textures[s_RendererData->TextureBindIndex] = spriteRenderer.m_Texture;
                textureID = s_RendererData->TextureBindIndex++;
            }
        }

        // Will either be 0 or a number referring to a texture bind unit
        quad.SetTextureID(textureID);
        auto vertData = quad.ToVertexData();
        glm::mat4 t(transform);

        uint32_t spaceNeeded = (uint32_t)(VERTEX_SIZE + sizeof(glm::mat4)) * vertData.size();
        if (s_RendererData->SpriteBatch.IsFull() || !s_RendererData->SpriteBatch.HasSpace(spaceNeeded)) {
            FlushAndBegin();
        }

        // Write data to vertex buffer and increment batch size
        s_RendererData->SpriteBatch.AddVertices(vertData, &t, sizeof(glm::mat4));
    }

    void Renderer::Clear() {
        GLStateManager::Clear();
    }

    void Renderer::Flush() {
        // Bind all textures
        for (uint32_t i = 0; i < s_RendererData->TextureBindIndex; i++) {
            s_RendererData->Textures[i]->SetBindingUnit(i);
            s_RendererData->Textures[i]->Bind();
        }

        // Bind vertex array and shader for batch and draw
        s_RendererData->DefaultShader->Bind();
        s_RendererData->SpriteBatch.Flush();

        // Reset data
        s_RendererData->TextureBindIndex = 1;
    }

    void Renderer::FlushAndBegin() {
        Flush();
        s_RendererData->Framebuffer->Bind();
    }
}