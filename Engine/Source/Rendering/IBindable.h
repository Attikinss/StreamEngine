#pragma once
#include <memory>

namespace SE {
	class IBindable {
	public:
		IBindable() = default;
		virtual ~IBindable() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	protected:
		uint32_t m_Handle = 0;
	};
}