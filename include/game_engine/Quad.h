#pragma once

#include "GameObject.h"

namespace ge {

///
/// \brief The Quad class is a Game Object that is a flat square.
///
class Quad : public GameObject {
public:
    ///
    /// \brief Quad Creates a quad with the specified number of times to repeate the texture.
    /// \param imageFilepath Filepath of the image texture.
    /// \param numTextureRepeat Number of times to repeat the texture in the x and y directions.
    ///
    Quad(const std::string &imageFilepath,
         const glm::vec2 &numTextureRepeat = glm::vec2(1.0f));

private:
    std::string imageFilepath;
};

} // namespace ge
