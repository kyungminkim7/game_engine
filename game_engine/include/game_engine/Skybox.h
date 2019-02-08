#pragma once

#include <string>
#include <array>

namespace ge {

class ShaderProgram;

///
/// \brief The Skybox class represents a skybox loaded from a cubemap.
///
class Skybox {
public:
    ///
    /// \brief Skybox Creates a cubemap for a skybox.
    /// \param imageFilepaths 6 images for each side of the skybox in the order of:
    ///                       right, left, top, bottom, front, back
    /// \exception ge::LoadError Failed to load texture data from image file.
    ///
    Skybox(const std::array<std::string, 6> &imageFilepaths);
    ~Skybox();

    void render(ShaderProgram *shader);

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int texture;
};

} // namespace ge
