#pragma once
#include "BufferLayout.h"
#include <memory>

namespace SE {
	class VertexBuffer {
	public:
		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(uint32_t size, void* data);

		VertexBuffer(uint32_t size);
		VertexBuffer(uint32_t size, void* data);
		~VertexBuffer();

		void Bind();
		void Unbind();

		void SetData(uint32_t size, void* data, uint32_t offset = 0);
		void SetLayout(const BufferLayout& layout) {
			m_Layout = layout;
		}

		BufferLayout& GetLayout() {
			return m_Layout;
		}

	private:
		uint32_t m_Handle = 0;
		uint32_t m_Size = 0;

		BufferLayout m_Layout;
	};
}