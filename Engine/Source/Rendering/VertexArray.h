#pragma once
#include "VertexBuffer.h"
#include <vector>

namespace SE {
	class VertexArray {
	public:
		static std::shared_ptr<VertexArray> Create();

		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {
			return m_VertexBuffers;
		}

	private:
		uint32_t m_Handle = 0;
		uint32_t m_AttributeCount = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	};
}