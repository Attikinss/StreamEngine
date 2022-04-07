#include "StreamEnginePCH.h"
#include "VertexBuffer.h"
#include <glad/gl.h>

namespace SE {
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		return std::make_shared<VertexBuffer>(size);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size, void* data) {
		return std::make_shared<VertexBuffer>(size, data);
	}

	VertexBuffer::VertexBuffer(uint32_t size)
		: m_Size(size) {
		// Create buffer and assign size but leave it empty
		glCreateBuffers(1, &m_Handle);
		glNamedBufferData(m_Handle, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(uint32_t size, void* data)
		: m_Size(size) {
		// Create and write to buffer
		glCreateBuffers(1, &m_Handle);
		glNamedBufferData(m_Handle, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_Handle);
		m_Handle = 0;
	}

	void VertexBuffer::SetData(uint32_t size, void* data, uint32_t offset) {
		void* buffer = glMapNamedBuffer(m_Handle, GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy((&buffer)[offset], data, size);
		glUnmapNamedBuffer(m_Handle);
	}

	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	}

	void VertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}