#pragma once
#include <string>
#include <vector>

namespace SE {
	enum class DataType {
		NONE = 0,
		BOOL,
		FLOAT, FLOAT2, FLOAT3, FLOAT4,
		INT, INT2, INT3, INT4,
		MAT3, MAT4,
	};

	static uint32_t ShaderDataTypeSize(DataType type) {
		switch (type) {
			case DataType::BOOL:     return 1;
			case DataType::FLOAT:    return 4;
			case DataType::FLOAT2:   return 4 * 2;
			case DataType::FLOAT3:   return 4 * 3;
			case DataType::FLOAT4:   return 4 * 4;
			case DataType::INT:      return 4;
			case DataType::INT2:     return 4 * 2;
			case DataType::INT3:     return 4 * 3;
			case DataType::INT4:     return 4 * 4;
			case DataType::MAT3:     return 4 * 3 * 3;
			case DataType::MAT4:     return 4 * 4 * 4;
		}

		return 0;
	}

	struct BufferElement {
		std::string Name;

		bool Normalised;
		bool Instanced;

		// The element's shader data type
		DataType Type;

		//The size of the element in bytes
		uint32_t Size;

		// The element's offset in the buffer
		uint32_t Offset;

		// VBO element default constructor
		BufferElement() = default;

		BufferElement(DataType type, const std::string& name, bool instanced = false, bool normalised = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Instanced(instanced), Normalised(normalised) {
		}

		uint32_t GetComponentCount() const {
			switch (Type) {
				case DataType::BOOL:    return 1;
				case DataType::FLOAT:   return 1;
				case DataType::FLOAT2:  return 2;
				case DataType::FLOAT3:  return 3;
				case DataType::FLOAT4:  return 4;
				case DataType::INT:     return 1;
				case DataType::INT2:    return 2;
				case DataType::INT3:    return 3;
				case DataType::INT4:    return 4;
				case DataType::MAT3:    return 3 * 3;
				case DataType::MAT4:    return 4 * 4;
			}

			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		uint32_t GetElementCount() const { return (uint32_t)m_Elements.size(); }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		// Calculates the offsets and stride of all elements in the layout
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		// Collection of elements in the layout
		std::vector<BufferElement> m_Elements;

		// The running stride of each element
		uint32_t m_Stride = 0;
	};
}