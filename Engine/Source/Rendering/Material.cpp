#include "StreamEnginePCH.h"
#include "Material.h"
#include "Shader.h"

namespace SE {
	std::shared_ptr<Material> Material::Create(const std::shared_ptr<Shader>& shader) {
		return std::make_shared<Material>(shader);
	}

	Material::Material(const std::shared_ptr<Shader>& shader)
		: m_Shader(shader) {
	}

	void Material::Bind() {
		m_Shader->Bind();
	}

	void Material::SetBool(const std::string& name, bool value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetFloat(const std::string& name, float value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetInt(const std::string& name, int32_t value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetUint(const std::string& name, uint32_t value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetVector2(const std::string& name, const glm::vec2& value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetVector3(const std::string& name, const glm::vec3& value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetVector4(const std::string& name, const glm::vec4& value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetMatrix3(const std::string& name, const glm::mat3& value) {
		m_Shader->SetUniform(name, value);
	}

	void Material::SetMatrix4(const std::string& name, const glm::mat4& value) {
		m_Shader->SetUniform(name, value);
	}
}