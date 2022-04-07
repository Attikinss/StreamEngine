#include "StreamEnginePCH.h"
#include "LayerStack.h"

namespace SE {
	LayerStack::LayerStack() {
		Logger::Trace("Layer stack created...");
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			// Shut down each layer before deleting
			layer->Shutdown();
			delete layer;
		}

		Logger::Trace("Layer stack destroyed...");
	}

	void LayerStack::AttachLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertionIndex, layer);
		m_LayerInsertionIndex++;

		layer->OnAttach();
	}

	void LayerStack::DetachLayer(Layer* layer) {
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertionIndex--;
		}

		layer->OnDetach();
	}
}