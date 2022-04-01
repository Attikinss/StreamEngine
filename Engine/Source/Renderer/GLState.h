#pragma once

namespace SE {
#pragma region Enums
	enum class StateType {
		BLEND = 3042,
		CULL_FACE = 2884,
		DEPTH_TEST = 2929,
		DITHER = 3024,
		MULTISAMPLE = 32925,
		SCISSOR_TEST = 3089,
		STENCIL_TEST = 2960,
	};

	enum class SrcFactor {
		CONSTANT_ALPHA = 32771,
		CONSTANT_COLOR = 32769,

		DST_ALPHA = 772,
		DST_COLOR = 774,

		ONE = 1,
		ONE_MINUS_CONSTANT_ALPHA = 32772,
		ONE_MINUS_CONSTANT_COLOR = 32770,
		ONE_MINUS_DST_ALPHA = 773,
		ONE_MINUS_DST_COLOR = 775,
		ONE_MINUS_SRC_ALPHA = 771,
		ONE_MINUS_SRC_COLOR = 769,

		SRC_ALPHA = 770,
		SRC_ALPHA_SATURATE = 776,
		SRC_COLOR = 768,

		ZERO = 0,
	};

	enum class DestFactor {
		CONSTANT_ALPHA = 32771,
		CONSTANT_COLOR = 32769,

		DST_ALPHA = 772,
		DST_COLOR = 774,

		ONE = 1,
		ONE_MINUS_CONSTANT_ALPHA = 32772,
		ONE_MINUS_CONSTANT_COLOR = 32770,
		ONE_MINUS_DST_ALPHA = 773,
		ONE_MINUS_DST_COLOR = 775,
		ONE_MINUS_SRC_ALPHA = 771,
		ONE_MINUS_SRC_COLOR = 769,

		SRC_ALPHA = 770,
		SRC_ALPHA_SATURATE = 776,
		SRC_COLOR = 768,

		ZERO = 0,
	};

	enum class CullMode {
		BACK = 1029,
		FRONT = 1028,
		FRONT_AND_BACK = 1032,
	};

	enum class DepthFunction {
		ALWAYS = 519,
		EQUAL = 514,
		GEQUAL = 518,
		GREATER = 516,
		LEQUAL = 515,
		LESS = 513,
		NEVER = 512,
		NOTEQUAL = 517,
	};

	enum class Primitive {
		LINES = 1,
		LINE_LOOP = 2,
		LINE_STRIP = 3,
		POINTS = 0,
		TRIANGLES = 4,
		TRIANGLE_STRIP = 5,
		TRIANGLE_FAN = 6,
	};
#pragma endregion

	class GLState {
	public:
		GLState(StateType state)
			: m_State((int)state), m_Enabled(false) {
		}

		void Enable() { SetEnabled(true); }
		void Disable() { SetEnabled(false); }
		void SetEnabled(bool enabled);

		bool IsEnabled() const { return m_Enabled; }

	private:
		const int m_State;
		bool m_Enabled;
	};

	class GLBlendState : public GLState {
	public:
		GLBlendState() : GLState(StateType::BLEND) {}

	public:
		int SrcRGB = (int)SrcFactor::ONE;
		int DestRGB = (int)SrcFactor::ZERO;
		int SrcAlpha = (int)SrcFactor::ONE;
		int DestAlpha = (int)SrcFactor::ZERO;
	};

	class GLCullState : public GLState {
	public:
		GLCullState() : GLState(StateType::CULL_FACE) {}

	public:
		int Mode = (int)CullMode::BACK;
	};

	class GLDepthState : public GLState {
	public:
		GLDepthState() : GLState(StateType::DEPTH_TEST) {}

	public:
		bool Mask = true;
		int Func = (int)DepthFunction::LESS;
	};
}