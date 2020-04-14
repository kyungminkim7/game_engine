#include <example_game/ExampleGame.h>

#include <glm/trigonometric.hpp>

#include <game_engine/Quad.h>

#include <game_engine/CameraFPV.h>

namespace ge {

std::unique_ptr<Game> ExampleGame::New(unsigned int windowWidth, unsigned int windowHeight,
                                    const std::string &windowTitle) {
    std::unique_ptr<ExampleGame> game(new ExampleGame(windowWidth, windowHeight, windowTitle));
    game->init();
    game->loadWorld();

    return game;
}

ExampleGame::ExampleGame(unsigned int windowWidth, unsigned int windowHeight, const std::string &windowTitle)
    : Game(windowWidth, windowHeight, windowTitle) {}

void ExampleGame::init() {
    Game::init();

    glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    this->setCam(std::make_unique<CameraFPV>(45.0f, static_cast<float>(this->getFrameBufferWidth()) / this->getFrameBufferHeight(),
                                             0.1f, 1000.0f));
    this->getCam()->setPosition({-3.0f, 0.0f, 3.0f});
}

void ExampleGame::loadWorld() {
    // Skybox
    auto skyboxDirPath = baseProjectPath + skyboxesDir + "mountain_sky/";
    std::array<std::string, 6> skyboxImageFilepaths {
        skyboxDirPath + "right.jpg",
        skyboxDirPath + "left.jpg",
        skyboxDirPath + "top.jpg",
        skyboxDirPath + "bottom.jpg",
        skyboxDirPath + "front.jpg",
        skyboxDirPath + "back.jpg"
    };
    this->setSkybox(std::make_unique<Skybox>(skyboxImageFilepaths));

    // Nanosuit
    auto nanosuit = std::make_shared<GameObject>(baseProjectPath + modelsDir + "nanosuit/nanosuit.obj");
    nanosuit->setScale(glm::vec3{0.3f})
            .rotate(glm::radians(90.0f), {1.0f, 0.0f, 0.0f})
            .rotate(glm::radians(-90.0f), {0.0f, 0.0f, 1.0f})
            .setPosition({3.0f, 0.0f, 0.0f});

    this->pushBackInWorldList(nanosuit);

    // Plane
    auto planeScale = 10.0f;
    auto plane = std::make_shared<Quad>(baseProjectPath + imagesDir + "marble.jpg", glm::vec2(planeScale));
    plane->setScale(glm::vec3(planeScale));
    this->pushBackInWorldList(plane);
}

} // namespace ge
