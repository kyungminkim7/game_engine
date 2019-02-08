#include <game_engine/Plane.h>

#include <algorithm>

#include <game_engine/Mesh.h>

namespace {

const std::vector<float> positions {
     0.5f, -0.5f,  0.0f,
     0.5f,  0.5f,  0.0f,
    -0.5f,  0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

const std::vector<float> normals {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};

const std::vector<float> textureCoords {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
};

const std::vector<unsigned int> indices {
    0, 1, 2,
    2, 3, 0
};

} // namespace

namespace ge {

Plane::Plane(const std::string &imageFilepath)
    : GameObject(positions, normals, textureCoords, indices, imageFilepath),
      imageFilepath(imageFilepath){}

GameObject& Plane::setTextureRepeat(float numRepeat) {
    std::vector<float> repeatTextureCoords;
    repeatTextureCoords.reserve(textureCoords.size());
    std::transform(textureCoords.cbegin(), textureCoords.cend(),
                   std::back_inserter(repeatTextureCoords),
                   [numRepeat](float tc){return tc * numRepeat;});

    this->setMesh(std::make_unique<Mesh>(positions, normals, repeatTextureCoords, indices,
                                         imageFilepath));
    return *this;
}

} // namespace ge
