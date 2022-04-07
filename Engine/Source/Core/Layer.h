#pragma once
#include <string>

namespace SE {
	class Layer {
	public:
		Layer(const std::string& name = "Layer")
			: m_DebugName(name) {
		}
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

		const std::string& GetNane() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}