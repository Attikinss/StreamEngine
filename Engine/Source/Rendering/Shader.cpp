#include "Shader.h"

#include "Core/Logger.h"
#include "Utilities/File.h"

#include <glad/gl.h>

namespace SE {
    namespace Utilities {
        static ShaderType GetTypeFromFilepath(const std::string& filepath) {
            std::string extension = filepath.substr(filepath.find_last_of('.') + 1);

            if (extension == "vert") {
                return ShaderType::VERTEX;
            }
            else if (extension == "frag") {
                return ShaderType::FRAGMENT;
            }
            else if (extension == "comp") {
                return ShaderType::COMPUTE;
            }
            else {
                return ShaderType::INVALID;
            }
        }

        static GLenum ShaderTypeToEnum(ShaderType type) {
            switch (type) {
                case SE::ShaderType::VERTEX:    return GL_VERTEX_SHADER;
                case SE::ShaderType::FRAGMENT:  return GL_FRAGMENT_SHADER;
                case SE::ShaderType::COMPUTE:   return GL_COMPUTE_SHADER;
                default:                        return GL_NONE;
            }
        }
    }

    std::shared_ptr<Shader> Shader::Create(const std::vector<std::string>& filepaths) {
        return std::make_shared<Shader>(filepaths);
    }

    std::shared_ptr<Shader> Shader::Create(const std::initializer_list<std::string>& filepaths) {
        return std::make_shared<Shader>(filepaths);
    }

    Shader::Shader(const std::vector<std::string>& filepaths) {
        std::unordered_map<ShaderType, std::string> sources;

        for (const auto& path : filepaths) {
            // Read source from file and get shader type from file extension
            std::string source = File::ReadAllText(path);
            ShaderType type = Utilities::GetTypeFromFilepath(path);

            if (!source.empty() && type != ShaderType::INVALID) {
                sources[type] = source;
            }
        }

        Compile(sources);
    }

    void Shader::Recompile() {

    }

    void Shader::Bind() {
        glUseProgram(m_Handle);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::Compile(const std::unordered_map<ShaderType, std::string>& sources) {
        if (sources.empty()) {
            Logger::Error("Failed to compile shader! No valid source code was provided.");
            return;
        }

        // Delete existing shader program handle first
        if (m_Handle) {
            glDeleteProgram(m_Handle);
        }

        // Create new shader program
        m_Handle = glCreateProgram();

        // Used to keep track of how many shaders were attached to the program
        std::vector<uint32_t> attachedShaders;

        for (const auto& source : sources) {
            // Create handle for shader
            uint32_t shaderHandle = glCreateShader(Utilities::ShaderTypeToEnum(source.first));

            // Copy source code into shader
            const char* cSourceCode = source.second.c_str();
            glShaderSource(shaderHandle, 1, &cSourceCode, nullptr);

            // Compile the shader
            glCompileShader(shaderHandle);

            // Check compilation status
            int success;
            char infoLog[1024];
            glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

            if (!success) {
                // Freak out if it didn't work
                glGetShaderInfoLog(shaderHandle, 1024, NULL, infoLog);
                Logger::Error("Shader compilation failed: [{0}]\n\t\t", m_Name, infoLog);

                // Delete the shader
                glDeleteShader(shaderHandle);
            }
            else {
                // Attach it to the shader program
                glAttachShader(m_Handle, shaderHandle);
                attachedShaders.push_back(shaderHandle);
            }
        }

        // Uh oh...
        if (attachedShaders.empty()) {
            glDeleteProgram(m_Handle);
            return;
        }

        // Link the program to the attached shaders
        glLinkProgram(m_Handle);

        // Check compilation status
        int success;
        char infoLog[1024];
        glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);

        if (!success) {
            // Freak out if it didn't work
            glGetProgramInfoLog(m_Handle, 1024, NULL, infoLog);
            Logger::Error("Shader linking failed\n{0}", infoLog);

            // Delete the shader program
            glDeleteProgram(m_Handle);
        }

        // Delete shaders now they're no longer in use
        for (auto& shader : attachedShaders) {
            glDeleteShader(shader);
        }

        // Clear for good measure
        attachedShaders.clear();

        glUseProgram(0);
    }

    void Shader::BindAttribute(uint32_t index, const std::string& name) {
        glBindAttribLocation(m_Handle, index, name.c_str());
    }

    uint32_t Shader::GetUniformLocation(const std::string& name) const {
        // Check that the uniform exists
        if (m_UniformLocations.find(name) != m_UniformLocations.end())
            return m_UniformLocations[name];

        int32_t uniformLocation = glGetUniformLocation(m_Handle, name.c_str());

        if (uniformLocation != -1) {
            m_UniformLocations[name] = uniformLocation;
        }
        else {
            Logger::Error("Invalid uniform name called: {0}", name);
        }

        return uniformLocation;
    }

    void Shader::SetUniform(const std::string& name, bool value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform1i(location, value ? 1: 0);
    }

    void Shader::SetUniform(const std::string& name, uint32_t value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform1ui(location, value);
    }

    void Shader::SetUniform(const std::string& name, int32_t value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform1i(location, value);
    }

    void Shader::SetUniform(const std::string& name, float value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform1f(location, value);
    }

    void Shader::SetUniform(const std::string& name, const glm::vec2& value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void Shader::SetUniform(const std::string& name, const glm::vec3& value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetUniform(const std::string& name, const glm::vec4& value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetUniform(const std::string& name, const glm::mat3& value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::SetUniform(const std::string& name, const glm::mat4& value) {
        GLint location = GetUniformLocation(name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }
}