#pragma once
#include "Vertex.h"
#include "VertexArray.h"

namespace SE {
	class Batch {
	public:
		Batch() = default;
		Batch(uint32_t maxVerts, BufferLayout layout);
		Batch(uint32_t maxVerts, uint32_t additionalSize, BufferLayout layout);
		~Batch() = default;

		void AddVertices(const std::vector<Vertex>& vertices);
		void AddVertices(const std::vector<Vertex>& vertices, void* perVertexData, uint32_t dataSize);
		void Flush();

		bool HasSpace(uint32_t size) const { return m_CurrentByteSize + size <= m_MaxByteSize; }
		bool IsFull() const { return m_CurrentByteSize >= m_MaxByteSize; }
		bool IsEmpty() const { return m_CurrentByteSize == 0; }

	private:
		std::shared_ptr<VertexArray> m_VertexArray;

		uint32_t m_MaxByteSize = 0;
		uint32_t m_CurrentByteSize = 0;

		uint32_t m_MaxVertices = 0;
		uint32_t m_VertexCount = 0;
	};
}