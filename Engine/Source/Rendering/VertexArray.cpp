#include "StreamEnginePCH.h"
#include "VertexArray.h"
#include <glad/gl.h>

namespace SE {
	static GLenum DataTypeToOpenGLType(DataType type) {
		switch (type) {
			case DataType::BOOL:
				return GL_BOOL;

			case DataType::FLOAT:
			case DataType::FLOAT2:
			case DataType::FLOAT3:
			case DataType::FLOAT4:
			case DataType::MAT3:
			case DataType::MAT4:
				return GL_FLOAT;

			case DataType::INT:
			case DataType::INT2:
			case DataType::INT3:
			case DataType::INT4:
				return GL_INT;
		}

		return GL_NONE;
	}

	std::shared_ptr<VertexArray> VertexArray::Create() {
		return std::make_shared<VertexArray>();
	}

	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_Handle);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_Handle);
		m_Handle = 0;
	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_Handle);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) {
		m_VertexBuffers.push_back(buffer);

		Bind();
		buffer->Bind();

		const BufferLayout& layout = buffer->GetLayout();
		std::vector<BufferElement> elements = layout.GetElements();
		
		uint32_t index = 0;
		uint32_t stride = layout.GetStride();

		for (const auto& element : elements) {
			uint32_t components = element.GetComponentCount();
			uint32_t valueType = DataTypeToOpenGLType(element.Type);
			uint32_t normalized = element.Normalised ? GL_TRUE : GL_FALSE;
			uint32_t offset = element.Offset;

			uint32_t glAttribs = components <= 4 ? 1 : (uint32_t)ceil(components / 4);
			for (uint32_t i = 0; i < glAttribs; i++, index++) {
				uint32_t dataOffset = (offset + components * i);

				glEnableVertexAttribArray(m_AttributeCount + index);
				glVertexAttribPointer(m_AttributeCount + index, components / glAttribs, valueType, normalized, stride, (void*)(uint64_t)dataOffset);

				if (element.Instanced) {
					glVertexAttribDivisor(m_AttributeCount + index, 1);
				}
			}
		}

		m_AttributeCount += index;
		buffer->Unbind();
		Unbind();
	}
}