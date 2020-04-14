#pragma once

#include "Camera.h"

namespace ge {

///
/// \brief First person shooter camera with a perspective view.
///
/// This camera pitches and yaws but does not allow roll.
///
class CameraFPV : public Camera {
public:
    CameraFPV(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane);

    ///
    /// \brief Camera movement controls through keyboard input.
    ///
    /// Implements the following movement controls:
    ///     1. 'w' - forward
    ///     2. 's' - backward
    ///     3. 'a' - left
    ///     4. 'd' - right
    ///
    /// This movement speed may be modified through Camera::setLinearSpeed().
    ///
    /// \param window The window that received the event.
    /// \param key The key that was pressed/released.
    /// \param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
    /// \param mods Bit field describing which modifier keys were held down.
    ///
    void keyCallback(GLFWwindow *window, int key, int action, int mods) override;

    ///
    /// \brief Controls camera through cursor movement.
    ///
    /// The camera rotates in place following the cursor movement.
    /// The sensitivity of this movement may be modified through Camera::setCursorSensitivity().
    ///
    /// \param window The window that received the event.
    /// \param cursorX The new cursor x-coordinate, relative to the left edge of the client area.
    /// \param cursorY The new cursor y-coordinate, relative to the top edge of the client area.
    ///
    void cursorPositionCallback(GLFWwindow *window, double cursorX, double cursorY) override;

    ///
    /// \brief onScrollInput Controls camera zoom through scrolling.
    /// \param window The window that received the event
    /// \param xOffset The scroll offset along the x-axis.
    /// \param yOffset The scroll offset along the y-axis.
    ///
    void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) override;

private:
    bool firstCursorPositionReceived = false;

    double lastCursorX = 0.0;
    double lastCursorY = 0.0;
};

} // namespace ge
