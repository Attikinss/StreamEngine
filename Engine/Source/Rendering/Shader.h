#pragma once
#include "IBindable.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

namespace SE {
	enum class ShaderType {
		INVALID = 0,
		VERTEX = 35633,
		FRAGMENT = 35632,
		COMPUTE = 37305
	};

	// TODO: Create Shader instances so that the same Shader
	//		 can be changed on a material to material basis
	class Shader : public IBindable {
	public:
		static std::shared_ptr<Shader> Create(const std::vector<std::string>& filepaths);
		static std::shared_ptr<Shader> Create(const std::initializer_list<std::string>& filepaths);

		Shader(const std::vector<std::string>& filepaths);

		void Recompile();
		void Bind() override;
		void Unbind() override;

		void BindAttribute(uint32_t index, const std::string& name);
		void SetUniform(const std::string& name, bool value);
		void SetUniform(const std::string& name, uint32_t value);
		void SetUniform(const std::string& name, int32_t value);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetUniform(const std::string& name, const glm::vec4& value);
		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

	private:
		uint32_t GetUniformLocation(const std::string& name) const;
		void Compile(const std::unordered_map<ShaderType, std::string>& sources);

	private:
		std::string m_Name;
		std::vector<std::string> m_Filepaths;

		mutable std::unordered_map<std::string, uint32_t> m_UniformLocations;
	};
}