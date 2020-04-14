#include <game_engine/Light.h>

namespace ge {

Light::Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    : ambient(ambient), diffuse(diffuse), specular(specular) {}

} // namespace ge
