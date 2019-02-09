#include <game_engine/Quad.h>

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

Quad::Quad(const std::string &imageFilepath, const glm::vec2 &numTextureRepeat)
    : GameObject() {
    std::vector<float> repeatTextureCoords(textureCoords);
    for (auto i = 0u; i < repeatTextureCoords.size(); ++i) {
        repeatTextureCoords[i] *= (i % 2 == 0 ? numTextureRepeat.x : numTextureRepeat.y);
    }

    this->setMesh(std::make_unique<Mesh>(positions, normals, repeatTextureCoords, indices,
                                         imageFilepath));
}

} // namespace ge
