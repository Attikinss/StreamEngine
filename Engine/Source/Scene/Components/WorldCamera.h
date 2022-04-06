#pragma once
#include "Component.h"
#include "Rendering/Camera.h"

namespace SE {
	class WorldCamera : public Component {
	public:
		WorldCamera() = default;
		~WorldCamera() = default;

		Camera& GetCamera() { return m_Camera;  }
		const Camera& GetCamera() const { return m_Camera;  }

		static const char* GetName() { return "WorldCamera"; }

	private:
		Camera m_Camera;
	};
}