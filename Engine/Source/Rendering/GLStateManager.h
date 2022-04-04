#pragma once
#include "GLState.h"

namespace SE {
	class GLStateManager {
	public:
		static void EnableCull();
		static void DisableCull();
		static void CullFace(CullMode mode);
		static void CullFace(int mode);

		static void EnableDepthTest();
		static void DisableDepthTest();
		static void DepthFunc(DepthFunction func);
		static void DepthFunc(int func);
		static void DepthMask(bool mask);

		static void EnableBlend();
		static void DisableBlend();
		static void BlendFunc(SrcFactor srcRgb, DestFactor destRgb);
		static void BlendFunc(int srcRgb, int destRgb);
		static void BlendFuncSeparate(SrcFactor srcRgb, DestFactor destRgb, SrcFactor srcAlpha, DestFactor destAlpha);
		static void BlendFuncSeparate(int srcRgb, int destRgb, int srcAlpha, int destAlpha);

		static void Clear();
		static void SetClearColour(float r, float g, float b, float a = 1.0f);
		static void SetPrimitive(Primitive primitive);
		static void DrawArrays(unsigned int count, unsigned int first = 0);
		static void InfoDump();
	};
}