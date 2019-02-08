#define GLM_ENABLE_EXPERIMENTAL

#include <game_engine/CameraNav.h>

#include <glm/trigonometric.hpp>

namespace ge {

CameraNav::CameraNav(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane)
    : Camera(maxFov_deg, aspectRatioWidthToHeight, nearPlane, farPlane) {}

void CameraNav::cursorPositionCallback(GLFWwindow *window, double cursorX, double cursorY) {
    auto leftMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    auto rightMouseButtonState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    auto xOffset = cursorX - this->lastCursorX;
    auto yOffset = cursorY - this->lastCursorY;

    auto deltaYaw = static_cast<float>(glm::radians(-xOffset * this->getCursorSensitivity()));
    auto deltaPitch = static_cast<float>(glm::radians(yOffset * this->getCursorSensitivity()));

    if (leftMouseButtonState == GLFW_PRESS || rightMouseButtonState == GLFW_PRESS) {
        this->rotate(deltaPitch, this->getOrientationY())
                .rotate(deltaYaw, this->getHorizontalRotationAxis());
    }

    this->lastCursorX = cursorX;
    this->lastCursorY = cursorY;
}

void CameraNav::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                this->moveBackward();
            } else {
                this->moveForward();
            }
        }
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            this->stopForwardBackwardMovement();
        }
    }
}

void CameraNav::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    this->setLinearSpeed(this->getLinearSpeed() + this->getScrollSensitivity() * yOffset);
}

} // namespace ge
