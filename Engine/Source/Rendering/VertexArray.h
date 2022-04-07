#pragma once
#include "IBindable.h"
#include "VertexBuffer.h"
#include <vector>

namespace SE {
	class VertexArray : public IBindable {
	public:
		static std::shared_ptr<VertexArray> Create();

		VertexArray();
		~VertexArray();

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {
			return m_VertexBuffers;
		}

	private:
		uint32_t m_AttributeCount = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	};
}