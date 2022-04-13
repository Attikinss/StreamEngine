#pragma once
#include "Component.h"

#include <string>

namespace SE {
	class EntityInfo : public Component {
	public:
		EntityInfo() = default;
		EntityInfo(const std::string& name, bool enabled = true)
			: Name(name) {
			IsEnabled = enabled;
		}

		void SetEnabled(bool enabled) {
			IsEnabled = enabled;
		}
		
		static const char* GetName() { return "EntityInfo"; }

	public:
		std::string Name = "Entity";
	};
}