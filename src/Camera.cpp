#define GLM_ENABLE_EXPERIMENTAL

#include <game_engine/Camera.h>

#include <glm/gtx/norm.hpp>

namespace {
constexpr float MIN_FOV_DEG = 1.0f;
}

namespace ge {
Camera::Camera(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane)
    : GameObject(),
      maxFov_deg(maxFov_deg), currentFov_deg(maxFov_deg), aspectRatioWidthToHeight(aspectRatioWidthToHeight),
      nearPlane(nearPlane), farPlane(farPlane),
      cursorSensitivity(0.1f), scrollSensitivity(2.0f), linearSpeed(10.0f),
      horizontalRotationAxis(0.0f, 0.0f, 1.0f) {}

void Camera::onUpdate(std::chrono::duration<float> updateDuration) {
    if (glm::length2(this->linearVelocity) > 0.0f) {
        this->translateInLocalFrame(this->linearVelocity * updateDuration.count());
    }
}

void Camera::setMaxFov(float fov_deg) {
    this->maxFov_deg = fov_deg;
}

void Camera::setCurrentFov_deg(float fov_deg) {
    if (fov_deg < MIN_FOV_DEG) {
        this->currentFov_deg = MIN_FOV_DEG;
    } else if (fov_deg > this->maxFov_deg) {
        this->currentFov_deg = this->maxFov_deg;
    } else {
        this->currentFov_deg = fov_deg;
    }
}

void Camera::setAspectRatioWidthToHeight(float aspectRatioWidthToHeight) {
    this->aspectRatioWidthToHeight = aspectRatioWidthToHeight;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(currentFov_deg),
                            aspectRatioWidthToHeight,
                            nearPlane, farPlane);
}

void Camera::setLinearSpeed(float linearSpeed) {
    this->linearSpeed = linearSpeed > 0.0f ? linearSpeed : 0.0f;
}

} // namespace ge
