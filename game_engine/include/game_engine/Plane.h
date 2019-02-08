#pragma once

#include "GameObject.h"

namespace ge {

///
/// \brief The Plane class is a Game Object that is a flat plane.
///
class Plane : public GameObject {
public:
    Plane(const std::string &imageFilepath);

    ///
    /// \brief setTextureRepeat Set the number of times to repeat the image texture in both s and r.
    /// \param numRepeat
    /// \return This GameObject reference.
    ///
    GameObject& setTextureRepeat(float numRepeat);

private:
    std::string imageFilepath;
};

} // namespace ge
