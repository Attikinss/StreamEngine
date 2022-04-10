#include "StreamEnginePCH.h"
#include "Renderer.h"

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
        std::shared_ptr<Shader> MissingMaterialShader;
        std::shared_ptr<Texture2D> WhitePixelTexture;

        glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);

        std::shared_ptr<Framebuffer> Framebuffer;
        std::shared_ptr<VertexArray> QuadVAO;
        std::shared_ptr<VertexArray> FramebufferVAO;

        RendererData() {
            auto fbVertData = Quad({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f }).ToVertexData();
            auto fbVBuffer = VertexBuffer::Create(sizeof(Vertex) * fbVertData.size(), fbVertData.data());
            fbVBuffer->SetLayout({
                { DataType::FLOAT3, "a_Position" },
                { DataType::FLOAT2, "a_UV" }
            });

            FramebufferVAO = VertexArray::Create();
            FramebufferVAO->AddVertexBuffer(fbVBuffer);

            Framebuffer = Framebuffer::Create({ 1280, 720, { FramebufferTextureFormat::RGBA8 } });

            std::vector<Vertex> vertData = Quad().ToVertexData();
            auto quadVBO = VertexBuffer::Create(sizeof(Vertex) * vertData.size(), vertData.data());
            quadVBO->SetLayout({
                { DataType::FLOAT3, "a_Position" },
                { DataType::FLOAT2, "a_UV" },
            });

            QuadVAO = VertexArray::Create();
            QuadVAO->AddVertexBuffer(quadVBO);

            FramebufferShader = Shader::Create({
                "Assets/Shaders/Framebuffer.vert",
                "Assets/Shaders/Framebuffer.frag"
            });

            MissingMaterialShader = Shader::Create({
                "Assets/Shaders/MissingMaterial.vert",
                "Assets/Shaders/MissingMaterial.frag"
            });

            WhitePixelTexture = Texture2D::Create("Assets/Textures/WhitePixel.png");
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
        //glm::vec3 viewPosition = glm::inverse(camera.GetView())[3];

        GLStateManager::Clear();
    }

    void Renderer::EndFrame() {
        s_RendererData->Framebuffer->Unbind();
        s_RendererData->Framebuffer->BindTexture(0);
        s_RendererData->FramebufferVAO->Bind();

        s_RendererData->FramebufferShader->Bind();
        s_RendererData->FramebufferShader->SetUniform("u_ColorAttachment", 0);

        GLStateManager::Clear();
        GLStateManager::DrawArrays(6, 0);
    }

    void Renderer::Submit(const SpriteRenderer& spriteRenderer, const glm::mat4& transform) {
        auto material = spriteRenderer.m_Material;
        if (!material.get()) {
            s_RendererData->MissingMaterialShader->Bind();
            s_RendererData->MissingMaterialShader->SetUniform("u_ViewProjectionMatrix", s_RendererData->ViewProjectionMatrix);
            s_RendererData->MissingMaterialShader->SetUniform("u_ModelMatrix", transform);
        }
        else {
            material->Bind();

            auto sprite = ResourceManager::Get().GetTextureLibrary().GetTexture(spriteRenderer.m_TextureHandle);
            if (!sprite.get()) {
                // Use a 1x1 white pixel for the shader
                s_RendererData->WhitePixelTexture->SetBindingUnit(0);
                s_RendererData->WhitePixelTexture->Bind();
            }
            else {
                sprite->SetBindingUnit(0);
                sprite->Bind();

                // Flipping on X or Y?
                material->SetBool("u_FlipX", spriteRenderer.FlipX);
                material->SetBool("u_FlipY", spriteRenderer.FlipY);
            }

            material->SetMatrix4("u_ViewProjectionMatrix", s_RendererData->ViewProjectionMatrix);
            material->SetMatrix4("u_ModelMatrix", transform);
            material->SetVector4("u_Color", spriteRenderer.Color);
            material->SetInt("u_Texture0", 0);
        }

        s_RendererData->QuadVAO->Bind();
        GLStateManager::DrawArrays(6, 0);
    }

    void Renderer::Clear() {
        GLStateManager::Clear();
    }
}