#include <game_engine/ShaderProgram.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <game_engine/Exception.h>

namespace {
constexpr unsigned int LOG_LENGTH = 1024;

///
/// \brief readFile Reads and returns a file's contents.
/// \param filepath Filepath of the file to read from.
/// \return File contents.
/// \exception std::ios_base::failure Failed to open the file.
///
std::string readFile(const std::string &filepath);

///
/// \brief compileShader Compiles a shader.
/// \param shaderType Type of shader to be created.
/// \param shaderPath Filepath of the shader's source code.
/// \return Compiled shader object.
/// \exception ge::BuildError Failed to compile shader.
///
unsigned int compileShader(unsigned int shaderType, const std::string &shaderPath);

///
/// \brief linkShaderProgram Links shaders to create a shader program.
///
/// This function does NOT delete the given shaders.
///
/// \param vertexShader Compiled vertex shader object.
/// \param fragmentShader Compiled fragment shader object.
/// \param geometryShader Compiled geometry shader object.
///                       0 if no geometry shader is used.
/// \return Linked shader program.
/// \exception ge::BuildError Failed to link shader.
///                           This function does NOT delete the given shaders.
///
unsigned int linkShaderProgram(unsigned int vertexShader,
                               unsigned int fragmentShader,
                               unsigned int geometryShader);

std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);

    // Check for valid file
    if (!file.is_open()) {
        std::stringstream errorMsg;
        errorMsg << "Failed to open file: " << filepath;
        throw std::ios_base::failure(errorMsg.str());
    }

    // Read file
    std::stringstream filestream;
    filestream << file.rdbuf();

    return filestream.str();
}

unsigned int compileShader(unsigned int shaderType, const std::string &shaderPath) {
    auto shaderCode = readFile(shaderPath);

    // Compile shader
    auto shader = glCreateShader(shaderType);
    auto shaderCodeStr = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderCodeStr, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char compileLog[LOG_LENGTH];
        glGetShaderInfoLog(shader, LOG_LENGTH, nullptr, compileLog);

        std::stringstream errorMsg;
        errorMsg << "Failed to compile " << shaderPath << "\n" << compileLog;

        glDeleteShader(shader);

        throw ge::BuildError(errorMsg.str());
    }

    return shader;
}

unsigned int linkShaderProgram(unsigned int vertexShader,
                               unsigned int fragmentShader,
                               unsigned int geometryShader) {
    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    if (geometryShader) glAttachShader(shaderProgram, geometryShader);

    int success;
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glDetachShader(shaderProgram, vertexShader);
        glDetachShader(shaderProgram, fragmentShader);
        if (geometryShader) glDetachShader(shaderProgram, geometryShader);

        char linkLog[LOG_LENGTH];
        glGetProgramInfoLog(shaderProgram, LOG_LENGTH, nullptr, linkLog);

        std::stringstream errorMsg;
        errorMsg << "Failed to link shaders\n" << linkLog;

        throw ge::BuildError(errorMsg.str());
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    if (geometryShader) glDetachShader(shaderProgram, geometryShader);

    return shaderProgram;
}

} // namespace

namespace ge {
ShaderProgram::ShaderProgram(const std::string &vertexShaderPath,
                             const std::string &fragmentShaderPath,
                             const std::string &geometryShaderPath) {
    // Compile shaders
    auto vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);

    unsigned int fragmentShader;
    try {
        fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    } catch (std::exception&) {
        glDeleteShader(vertexShader);
        throw;
    }

    auto geometryShader = 0u;
    if (!geometryShaderPath.empty()) {
        try {
            geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryShaderPath);
        } catch (std::exception&) {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            throw;
        }
    }

    // Link shaders
    try {
        this->id = linkShaderProgram(vertexShader, fragmentShader, geometryShader);
    } catch (std::exception&) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (geometryShader) glDeleteShader(geometryShader);
        throw;
    }
    std::cout << "Successfully compiled and linked shaders:\n"
              << vertexShaderPath << "\n" << fragmentShaderPath << "\n";
    if (geometryShader) std::cout << geometryShaderPath << "\n";
    std::cout << "\n";

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShader) glDeleteShader(geometryShader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->id);
}

ShaderProgram& ShaderProgram::use() {
    glUseProgram(this->id);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, bool value) {
    this->setUniform(name, value);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, const glm::vec2 &v) {
    glUniform2f(glGetUniformLocation(this->id, name.c_str()), v.x, v.y);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, const glm::vec3 &v) {
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), v.x, v.y, v.z);
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, const glm::mat3 &m) {
    glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    return *this;
}

ShaderProgram& ShaderProgram::setUniform(const std::string &name, const glm::mat4 &m) {
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    return *this;
}

ShaderProgram& ShaderProgram::setUniformBlockBinding(const std::string &uniformBlockName,
                                                     unsigned int bindingPoint) {
    glUniformBlockBinding(this->id, glGetUniformBlockIndex(this->id, uniformBlockName.c_str()), bindingPoint);
    return *this;
}
} // namespace ge
