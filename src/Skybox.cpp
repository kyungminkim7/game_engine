#include <game_engine/Skybox.h>

#include <glad/glad.h>
#include <stb_image.h>

#include <vector>

#include <game_engine/Exception.h>
#include <game_engine/ShaderProgram.h>

namespace {

const std::vector<float> skyboxVertices {
    // Positions
     -1.0f,  1.0f, -1.0f,
     -1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f,  1.0f, -1.0f,
     -1.0f,  1.0f, -1.0f,

     -1.0f, -1.0f,  1.0f,
     -1.0f, -1.0f, -1.0f,
     -1.0f,  1.0f, -1.0f,
     -1.0f,  1.0f, -1.0f,
     -1.0f,  1.0f,  1.0f,
     -1.0f, -1.0f,  1.0f,

      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,

     -1.0f, -1.0f,  1.0f,
     -1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f, -1.0f,  1.0f,
     -1.0f, -1.0f,  1.0f,

     -1.0f,  1.0f, -1.0f,
      1.0f,  1.0f, -1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
     -1.0f,  1.0f,  1.0f,
     -1.0f,  1.0f, -1.0f,

     -1.0f, -1.0f, -1.0f,
     -1.0f, -1.0f,  1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
     -1.0f, -1.0f,  1.0f,
      1.0f, -1.0f,  1.0f
};

unsigned int loadCubemapTexture(const std::array<std::string, 6> &imageFilepaths) {
    unsigned int texture;
    glGenTextures(1, &texture);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    int width, height, numChannels;
    for (auto i = 0u; i < imageFilepaths.size(); ++i) {
        auto image = stbi_load(imageFilepaths[i].c_str(),
                               &width, &height, &numChannels, 0);

        if (image) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height,
                         0, GL_RGB, GL_UNSIGNED_BYTE, image);
            stbi_image_free(image);
        } else {
            stbi_image_free(image);
            glDeleteTextures(1, &texture);
            throw ge::LoadError("Failed to load texture at " + imageFilepaths[i]);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return texture;
}

} // namespace

namespace ge {

Skybox::Skybox(const std::array<std::string, 6> &imageFilepaths) {
    // Load vertex data
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(skyboxVertices.size() * sizeof(float)),
                 skyboxVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(3 * sizeof(float)),
                          reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Load textures
    try {
        this->texture = loadCubemapTexture(imageFilepaths);
    } catch (std::exception&) {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }
}

Skybox::~Skybox() {
    glDeleteTextures(1, &this->texture);
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

void Skybox::render(ShaderProgram *shader) {
    glActiveTexture(GL_TEXTURE0);
    shader->setUniform("skybox", 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);

    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

} // namespace ge
