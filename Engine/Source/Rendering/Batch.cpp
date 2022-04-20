#include "StreamEnginePCH.h"
#include "Batch.h"

#include "GLStateManager.h"

namespace SE {
	Batch::Batch(uint32_t maxVerts, BufferLayout layout)
		: Batch(maxVerts, 0, layout) {
	}

	Batch::Batch(uint32_t maxVerts, uint32_t additionalSize, BufferLayout layout) {
		m_MaxByteSize = maxVerts * (VERTEX_SIZE + additionalSize);
		
		auto vertexBuffer = VertexBuffer::Create(m_MaxByteSize);
		vertexBuffer->SetLayout(layout);

		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(vertexBuffer);
	}

	void Batch::AddVertices(const std::vector<Vertex>& vertices) {
		uint32_t size = sizeof(Vertex) * vertices.size();
		if (m_CurrentByteSize + size > m_MaxByteSize || m_VertexCount + vertices.size() > m_MaxVertices) {
			Flush();
		}

		m_VertexArray->GetVertexBuffers()[0]->SetData(size, (void*)vertices.data(), m_CurrentByteSize);
		m_CurrentByteSize += size;
		m_VertexCount += vertices.size();
	}

	void Batch::AddVertices(const std::vector<Vertex>& vertices, void* perVertexData, uint32_t dataSize) {
		uint32_t size = (sizeof(Vertex) + dataSize) * vertices.size();
		if (m_CurrentByteSize + size > m_MaxByteSize) {
			Flush();
		}

		// Create buffer for this quad
		char* buffer = new char[size];
		uint32_t bufferSize = 0;

		for (size_t i = 0; i < vertices.size(); i++) {
			memcpy(&buffer[bufferSize], &vertices[i], VERTEX_SIZE);
			bufferSize += VERTEX_SIZE;

			memcpy(&buffer[bufferSize], perVertexData, dataSize);
			bufferSize += dataSize;
		}

		m_VertexArray->GetVertexBuffers()[0]->SetData(bufferSize, buffer, m_CurrentByteSize);
		m_CurrentByteSize += bufferSize;
		m_VertexCount += vertices.size();
	}

	void Batch::Flush() {
		if (IsEmpty()) {
			return;
		}

		m_VertexArray->Bind();
		m_VertexArray->GetVertexBuffers()[0]->Bind();
		GLStateManager::DrawArrays(m_VertexCount, 0);

		m_VertexCount = 0;
		m_CurrentByteSize = 0;
	}
}