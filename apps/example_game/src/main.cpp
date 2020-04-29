#include <memory>

#include <example_game/ExampleGame.h>

std::unique_ptr<ge::Game> game;

void setGlobalSettings();
void setGameCallbacks();
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow *window, double x, double y);
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

int main() {
    setGlobalSettings();
    game = ge::ExampleGame::New(2000, 1600, "Test Game");
    setGameCallbacks();

    game->startGameLoop();

    return 0;
}

void setGlobalSettings() { }

void setGameCallbacks() {
    glfwSetFramebufferSizeCallback(game->getWindow(), &frameBufferSizeCallback);
    glfwSetCursorPosCallback(game->getWindow(), &cursorPositionCallback);
    glfwSetMouseButtonCallback(game->getWindow(), &mouseButtonCallback);
    glfwSetKeyCallback(game->getWindow(), &keyCallback);
    glfwSetScrollCallback(game->getWindow(), &scrollCallback);
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    game->frameBufferSizeCallback(window, width, height);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    game->keyCallback(window, key, scancode, action, mods);
}

void cursorPositionCallback(GLFWwindow *window, double x, double y) {
    game->cursorPositionCallback(window, x, y);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    game->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    game->scrollCallback(window, xOffset, yOffset);
}
