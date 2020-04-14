#pragma once

#include "Camera.h"

namespace ge {

///
/// \brief Camera for navigating around a scene.
///
class CameraNav : public Camera {
public:
    CameraNav(float maxFov_deg, float aspectRatioWidthToHeight, float nearPlane, float farPlane);

    ///
    /// \brief Controls pan and tilt of the camera.
    ///
    /// Press and drag either the left or right mouse button to rotate the camera in place
    /// following the cursor movement. The sensitivity of this movement may be modified through
    /// Camera::setCursorSensitivity().
    ///
    /// \param window The window that received the event.
    /// \param cursorX The new cursor x-coordinate, relative to the left edge of the client area.
    /// \param cursorY The new cursor y-coordinate, relative to the top edge of the client area.
    ///
    void cursorPositionCallback(GLFWwindow *window, double cursorX, double cursorY) override;

    ///
    /// \brief mouseButtonCallback Controls forward and backward movement of the camera.
    ///
    /// Press the right mouse button to move forward. Press the right button while pressing the
    /// left SHIFT key to move backward. Release the mouse button to stop.
    ///
    /// \param window The window that received the event.
    /// \param button The button that was pressed/released.
    /// \param action GLFW_PRESS/GLFW_RELEASE.
    /// \param mods Bit field describing which modifier keys were held down.
    ///
    void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) override;

    ///
    /// \brief onScrollInput Controls camera zoom through scrolling.
    /// \param window The window that received the event
    /// \param xOffset The scroll offset along the x-axis.
    /// \param yOffset The scroll offset along the y-axis.
    ///
    void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) override;

private:
    double lastCursorX = 0.0;
    double lastCursorY = 0.0;
};

} // namespace ge
