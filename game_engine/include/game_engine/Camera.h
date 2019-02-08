#pragma once

#include "GameObject.h"

#include <chrono>

#include <GLFW/glfw3.h>

namespace ge {

///
/// \brief Represents a Camera.
///
class Camera : public GameObject {
public:
    ///
    /// \brief Camera constructor.
    ///
    /// Sets the following default values:
    ///     1. mouse sensitivity  = 0.1
    ///     2. scroll sensitivity = 2.0
    ///     3. movement speed     = 10.0 m/s
    ///     4. rotation axis      = {0, 0, 1}
    ///     5. look at direction  = {1, 0, 0}
    ///     6. normal direction   = {0, 0, 1}
    ///     7. current fov        = max fov
    ///
    /// \param maxFov_deg Camera field of view in degrees.
    /// \param aspectRatioWidthToHeight
    /// \param nearPlane Distance to camera near plane in m.
    /// \param farPlane Distance to camera far plane in m.
    ///
    Camera(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane);

    ///
    /// \brief Updates the camera state.
    ///
    /// This should be called on every iteration of the game loop.
    ///
    /// \param updateDuration Elapsed time since the last frame.
    ///
    void onUpdate(std::chrono::duration<float> updateDuration) override;

    void setMaxFov(float fov_deg);

    ///
    /// \brief Sets the camera's current field of view.
    ///
    /// The fov is capped between 1.0 and the supplied max field of view.
    ///
    /// \param fov_deg
    ///
    void setCurrentFov_deg(float fov_deg);
    float getCurrentFov_deg() const;

    void setAspectRatioWidthToHeight(float aspectRatioWidthToHeight);

    glm::mat4 getProjectionMatrix() const;

    ///
    /// \brief Sets the speed of the camera's linear movements.
    /// \param linearSpeed Linear movement speed (m/s).
    ///
    void setLinearSpeed(float linearSpeed);
    float getLinearSpeed() const;

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void stopForwardBackwardMovement();
    void stopSidewaysMovement();

    ///
    /// \brief setCursorSenstivity Sets the sensitivity of the camera's rotation following
    ///                            the cursor's movements.
    /// \param cursorSensitivity
    ///
    void setCursorSenstivity(float cursorSensitivity);
    float getCursorSensitivity() const;

    ///
    /// \brief setScrollSensitivity Sets the sensitivity of the camera's zoom through scrolling.
    /// \param scrollSensitivity
    ///
    void setScrollSensitivity(float scrollSensitivity);
    float getScrollSensitivity() const;

    void setHorizontalRotationAxis(const glm::vec3& horizontalRotationAxis);
    glm::vec3 getHorizontalRotationAxis() const;

private:
    float maxFov_deg;
    float currentFov_deg;
    float aspectRatioWidthToHeight;
    float nearPlane; ///< m
    float farPlane;  ///< m

    float cursorSensitivity;
    float scrollSensitivity;

    float linearSpeed; ///< Speed of each linear velocity component (m/s)
    glm::vec3 linearVelocity {0.0f};

    glm::vec3 horizontalRotationAxis;

    glm::mat4 projectionMatrix {1.0f};
};

inline float Camera::getCurrentFov_deg() const {return this->currentFov_deg;}

inline float Camera::getLinearSpeed() const {return this->linearSpeed;}

inline void Camera::moveForward() {this->linearVelocity.x = this->linearSpeed;}
inline void Camera::moveBackward() {this->linearVelocity.x = -this->linearSpeed;}
inline void Camera::moveLeft() {this->linearVelocity.y = this->linearSpeed;}
inline void Camera::moveRight() {this->linearVelocity.y = -this->linearSpeed;}
inline void Camera::stopForwardBackwardMovement() {this->linearVelocity.x = 0;}
inline void Camera::stopSidewaysMovement() {this->linearVelocity.y = 0;}

inline void Camera::setCursorSenstivity(float cursorSensitivity) {
    this->cursorSensitivity = cursorSensitivity;
}

inline float Camera::getCursorSensitivity() const {return this->cursorSensitivity;}

inline void Camera::setScrollSensitivity(float scrollSensitivity) {
    this->scrollSensitivity = scrollSensitivity;
}

inline float Camera::getScrollSensitivity() const {return this->scrollSensitivity;}

inline void Camera::setHorizontalRotationAxis(const glm::vec3 &yawAxis) {
    this->horizontalRotationAxis = yawAxis;
}

inline glm::vec3 Camera::getHorizontalRotationAxis() const {
    return this->horizontalRotationAxis;
}

} // namespace ge
