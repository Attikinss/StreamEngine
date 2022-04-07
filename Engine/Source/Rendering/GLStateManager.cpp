#include "StreamEnginePCH.h"
#include "GLStateManager.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace SE {
	struct Color {
		float R;
		float G;
		float B;
		float A;
	};

	struct GLStateInfo {
		GLCullState CullState;
		GLBlendState BlendState;
		GLDepthState DepthState;

		Color ClearColour;
		Primitive DrawPrimitive = Primitive::TRIANGLES;
	};

	static GLStateInfo s_StateInfo;

	static bool s_GladInitialized = false;

	static void CheckGladState() {
		if (s_GladInitialized) {
			return;
		}

		// Initialize glad
		// A context MUST be set before this can return a successful result
		int gladStatus = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		_ASSERT(gladStatus);
		s_GladInitialized = true;
	}

	void GLStateManager::EnableCull() {
		CheckGladState();
		s_StateInfo.CullState.Enable();
	}

	void GLStateManager::DisableCull() {
		CheckGladState();
		s_StateInfo.CullState.Disable();
	}

	void GLStateManager::CullFace(CullMode mode) {
		CheckGladState();
		CullFace((int)mode);
	}

	void GLStateManager::CullFace(int mode) {
		CheckGladState();
		s_StateInfo.CullState.Mode = mode;
		glCullFace(mode);
	}

	void GLStateManager::EnableDepthTest() {
		CheckGladState();
		s_StateInfo.DepthState.Enable();
	}

	void GLStateManager::DisableDepthTest() {
		CheckGladState();
		s_StateInfo.DepthState.Disable();
	}

	void GLStateManager::DepthFunc(DepthFunction func) {
		DepthFunc((int)func);
	}

	void GLStateManager::DepthFunc(int func) {
		CheckGladState();
		if (func == s_StateInfo.DepthState.Func) {
			return;
		}

		s_StateInfo.DepthState.Func = func;
		glDepthFunc(func);
	}

	void GLStateManager::DepthMask(bool mask) {
		CheckGladState();
		if (mask == s_StateInfo.DepthState.Mask) {
			return;
		}

		s_StateInfo.DepthState.Mask = mask;
		glDepthMask(mask);
	}

	void GLStateManager::EnableBlend() {
		CheckGladState();
		s_StateInfo.BlendState.Enable();
	}

	void GLStateManager::DisableBlend() {
		CheckGladState();
		s_StateInfo.BlendState.Disable();
	}

	void GLStateManager::BlendFunc(SrcFactor srcRgb, DestFactor destRgb) {
		BlendFunc((int)srcRgb, (int)destRgb);
	}

	void GLStateManager::BlendFunc(int srcRgb, int destRgb) {
		CheckGladState();
		if (srcRgb == s_StateInfo.BlendState.SrcRGB && destRgb == s_StateInfo.BlendState.DestRGB) {
			return;
		}

		s_StateInfo.BlendState.SrcRGB = srcRgb;
		s_StateInfo.BlendState.DestRGB = destRgb;

		glBlendFunc(srcRgb, destRgb);
	}

	void GLStateManager::BlendFuncSeparate(SrcFactor srcRgb, DestFactor destRgb, SrcFactor srcAlpha, DestFactor destAlpha) {
		BlendFuncSeparate((int)srcRgb, (int)destRgb, (int)srcAlpha, (int)destAlpha);
	}

	void GLStateManager::BlendFuncSeparate(int srcRgb, int destRgb, int srcAlpha, int destAlpha) {
		CheckGladState();

		if (srcRgb == s_StateInfo.BlendState.SrcRGB && destRgb == s_StateInfo.BlendState.DestRGB &&
			srcAlpha == s_StateInfo.BlendState.SrcAlpha && destAlpha == s_StateInfo.BlendState.DestAlpha) {
			return;
		}

		s_StateInfo.BlendState.SrcRGB = srcRgb;
		s_StateInfo.BlendState.DestRGB = destRgb;
		s_StateInfo.BlendState.SrcAlpha = srcAlpha;
		s_StateInfo.BlendState.DestAlpha = destAlpha;

		glBlendFuncSeparate(srcRgb, destRgb, srcAlpha, destAlpha);
	}

	void GLStateManager::Clear() {
		CheckGladState();

		int flags = GL_COLOR_BUFFER_BIT;
		if (s_StateInfo.DepthState.IsEnabled()) {
			flags |= GL_DEPTH_BUFFER_BIT;
		}

		glClear(flags);
	}

	void GLStateManager::SetClearColour(float r, float g, float b, float a) {
		CheckGladState();
		s_StateInfo.ClearColour = { r, g, b, a };
		glClearColor(r, g, b, a);
	}

	void GLStateManager::SetPrimitive(Primitive primitive) {
		s_StateInfo.DrawPrimitive = primitive;
	}

	void GLStateManager::DrawArrays(unsigned int count, unsigned int first) {
		CheckGladState();
		glDrawArrays((unsigned int)s_StateInfo.DrawPrimitive, first, count);
	}

	void GLStateManager::InfoDump() {
		CheckGladState();
		Logger::Info("OpenGL Info:\n\tVersion: {0}\n\tVendor: {1}\n\tDevice: {2}",
			glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	}
}