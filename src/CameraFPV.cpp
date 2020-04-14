#define GLM_ENABLE_EXPERIMENTAL

#include <game_engine/CameraFPV.h>

#include <glm/trigonometric.hpp>

namespace ge {

CameraFPV::CameraFPV(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane)
    : Camera(maxFov_deg, aspectRatioWidthToHeight, nearPlane, farPlane) {}

void CameraFPV::keyCallback(GLFWwindow *window, int key, int action, int mods) {
    auto forwardKeyStatus = glfwGetKey(window, GLFW_KEY_W);
    auto backwardKeyStatus = glfwGetKey(window, GLFW_KEY_S);
    auto leftKeyStatus = glfwGetKey(window, GLFW_KEY_A);
    auto rightKeyStatus = glfwGetKey(window, GLFW_KEY_D);

    if (forwardKeyStatus == GLFW_PRESS && backwardKeyStatus == GLFW_RELEASE) {
        this->moveForward();
    }

    if (backwardKeyStatus == GLFW_PRESS && forwardKeyStatus == GLFW_RELEASE) {
        this->moveBackward();
    }

    if (leftKeyStatus == GLFW_PRESS && rightKeyStatus == GLFW_RELEASE) {
        this->moveLeft();
    }

    if (rightKeyStatus == GLFW_PRESS && leftKeyStatus == GLFW_RELEASE) {
        this->moveRight();
    }

    if (forwardKeyStatus == GLFW_RELEASE && backwardKeyStatus == GLFW_RELEASE) {
        this->stopForwardBackwardMovement();
    }

    if (leftKeyStatus == GLFW_RELEASE && rightKeyStatus == GLFW_RELEASE) {
        this->stopSidewaysMovement();
    }
}

void CameraFPV::cursorPositionCallback(GLFWwindow *window, double cursorX, double cursorY) {
    if (!firstCursorPositionReceived) {
        this->lastCursorX = cursorX;
        this->lastCursorY = cursorY;
        firstCursorPositionReceived = true;
    }

    auto xOffset = cursorX - this->lastCursorX;
    auto yOffset = cursorY - this->lastCursorY;

    auto deltaYaw = static_cast<float>(glm::radians(-xOffset * this->getCursorSensitivity()));
    auto deltaPitch = static_cast<float>(glm::radians(yOffset * this->getCursorSensitivity()));

    this->rotate(deltaPitch, this->getOrientationY())
            .rotate(deltaYaw, this->getHorizontalRotationAxis());

    this->lastCursorX = cursorX;
    this->lastCursorY = cursorY;
}

void CameraFPV::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    this->setCurrentFov_deg(static_cast<float>(this->getCurrentFov_deg() -
                                           this->getScrollSensitivity() * yOffset));
}

} // namespace ge
