#pragma once
#include <memory>
#include <string>

#include <glm/glm.hpp>

namespace SE {
	class Shader;

	class Material {
	public:
		static std::shared_ptr<Material> Create(const std::shared_ptr<Shader>& shader);
		Material(const std::shared_ptr<Shader>& shader);
		~Material() = default;

		// ** Temporary **
		void Bind();

		void SetBool(const std::string& name, bool value);
		void SetFloat(const std::string& name, float value);
		void SetInt(const std::string& name, int32_t value);
		void SetUint(const std::string& name, uint32_t value);
		void SetVector2(const std::string& name, const glm::vec2& value);
		void SetVector3(const std::string& name, const glm::vec3& value);
		void SetVector4(const std::string& name, const glm::vec4& value);
		void SetMatrix3(const std::string& name, const glm::mat3& value);
		void SetMatrix4(const std::string& name, const glm::mat4& value);

	private:
		std::shared_ptr<Shader> m_Shader;
	};
}