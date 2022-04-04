#pragma once
#include <memory>

namespace SE {
	class IBindable {
	public:
		IBindable() = default;
		virtual ~IBindable() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

	protected:
		uint32_t m_Handle = 0;
	};
}