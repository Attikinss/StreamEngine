#pragma once
#include <glm/glm.hpp>

namespace SE {
	class Camera;
	class SpriteRenderer;
	struct Quad;

	class Renderer {
	public:
		static bool Initialize();
		static bool Shutdown();

		static void BeginFrame(const Camera& camera);
		static void EndFrame();
		static void Submit(const SpriteRenderer& spriteRenderer, const glm::mat4& transform, Quad& quad);
		static void Clear();

	private:
		static void Flush();
		static void FlushAndBegin();
	};
}