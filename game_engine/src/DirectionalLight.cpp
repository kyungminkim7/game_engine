#include <game_engine/DirectionalLight.h>

#include <glm/gtc/matrix_transform.hpp>

namespace ge {

DirectionalLight::DirectionalLight(float left, float right, float bottom, float top, float nearPlane, float farPlane)
    : left(left), right(right), bottom(bottom), top(top),
      nearPlane(nearPlane), farPlane(farPlane) {}

glm::mat4 DirectionalLight::getProjectionMatrix() const {
    return glm::ortho(this->left, this->right, this->bottom, this->top,
                      this->nearPlane, this->farPlane);
}

} // namespace ge
