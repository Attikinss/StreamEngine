#pragma once
#include <glm/glm.hpp>

namespace SE {
	struct Vertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 UV;
		float TextureID;
	};

	constexpr static uint32_t VERTEX_SIZE = sizeof(Vertex);
}