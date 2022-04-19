#pragma once
#include "Vertex.h"

#include <vector>

namespace SE {
	struct Quad {
		Vertex Vertices[4];

        Quad() : Quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }) {
        }

        Quad(const glm::vec3& position, const glm::vec2& scale) {
            Vertices[0].Position = position + glm::vec3(-scale.x * 0.5f, -scale.y * 0.5f, 0.0f);
            Vertices[1].Position = position + glm::vec3(-scale.x * 0.5f,  scale.y * 0.5f, 0.0f);
            Vertices[2].Position = position + glm::vec3( scale.x * 0.5f,  scale.y * 0.5f, 0.0f);
            Vertices[3].Position = position + glm::vec3( scale.x * 0.5f, -scale.y * 0.5f, 0.0f);

            Vertices[0].UV = { 0.0f, 0.0f };
            Vertices[1].UV = { 0.0f, 1.0f };
            Vertices[2].UV = { 1.0f, 1.0f };
            Vertices[3].UV = { 1.0f, 0.0f };

            Vertices[0].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
            Vertices[1].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
            Vertices[2].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
            Vertices[3].Color = { 1.0f, 1.0f, 1.0f, 1.0f };

            Vertices[0].TextureID = 0.0f;
            Vertices[1].TextureID = 0.0f;
            Vertices[2].TextureID = 0.0f;
            Vertices[3].TextureID = 0.0f;

        }

        void SetTextureID(uint32_t id) {
            Vertices[0].TextureID = (float)id;
            Vertices[1].TextureID = (float)id;
            Vertices[2].TextureID = (float)id;
            Vertices[3].TextureID = (float)id;
        }

        void SetColor(const glm::vec4& color) {
            Vertices[0].Color = color;
            Vertices[1].Color = color;
            Vertices[2].Color = color;
            Vertices[3].Color = color;
        }

        void FlipX() {
            Vertices[0].UV.x = 1.0f - Vertices[0].UV.x;
            Vertices[1].UV.x = 1.0f - Vertices[1].UV.x;
            Vertices[2].UV.x = 1.0f - Vertices[2].UV.x;
            Vertices[3].UV.x = 1.0f - Vertices[3].UV.x;
        }

        void FlipY() {
            Vertices[0].UV.y = 1.0f - Vertices[0].UV.y;
            Vertices[1].UV.y = 1.0f - Vertices[1].UV.y;
            Vertices[2].UV.y = 1.0f - Vertices[2].UV.y;
            Vertices[3].UV.y = 1.0f - Vertices[3].UV.y;
        }

        std::vector<Vertex> ToVertexData() const {
            return std::vector<Vertex>({ Vertices[0], Vertices[1], Vertices[2], Vertices[2], Vertices[3], Vertices[0] });
        }
	};
}