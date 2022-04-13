#pragma once
namespace SE {
	class Component {
	public:
		Component() = default;
		virtual ~Component() = default;

	public:
		bool IsEnabled = true;
	};
}