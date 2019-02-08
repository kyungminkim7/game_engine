#include <game_engine/Game.h>

#include <iostream>
#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <game_engine/Exception.h>

namespace {
const std::string matricesUboName = "Matrices";
const auto mat4Size_bytes = sizeof(glm::mat4);
} // namespace

namespace ge {

int Game::glContextMajorVersion = 3;
int Game::glContextMinorVersion = 3;

std::string Game::baseProjectPath = "../../";
std::string Game::shadersDir = "shaders/";
std::string Game::modelsDir = "models/";
std::string Game::skyboxesDir = "skyboxes/";

std::unique_ptr<Game> Game::New(unsigned int windowWidth, unsigned int windowHeight,
                                const std::string &windowTitle) {
    std::unique_ptr<Game> game(new Game(windowWidth, windowHeight, windowTitle));
    game->init();
    game->loadWorld();

    return game;
}

Game::Game(unsigned int windowWidth, unsigned int windowHeight, const std::string &windowTitle)
    : lastUpdateTime(std::chrono::system_clock::now()) {

    // Initialize context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glContextMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glContextMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "Initialized GLFW.\n";

    // Create window
    this->window = WindowPtr(glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(),
                                              nullptr, nullptr),
                             [](GLFWwindow*){glfwTerminate();});

    if (this->window == nullptr) {
        glfwTerminate();
        throw ge::WindowingSystemError("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(this->window.get());

    // Load OpenGL extensions
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwSwapInterval(1);
        std::cout << "Initialized GLAD.\n";
    } else {
        throw ge::GlExtensionLoadingError("Failed to initialize GLAD.");
    }

    // Set up main framebuffer size
    glfwGetFramebufferSize(this->window.get(), &this->frameBufferWidth, &this->frameBufferHeight);
    glViewport(0, 0, this->frameBufferWidth, this->frameBufferHeight);

    // Set up shaders
    const auto shadersDirPath = baseProjectPath + shadersDir;
    this->defaultShader = std::make_unique<ShaderProgram>(shadersDirPath + "default.vert",
                                                          shadersDirPath + "default.frag");
    this->skyboxShader = std::make_unique<ShaderProgram>(shadersDirPath + "skybox.vert",
                                                         shadersDirPath + "skybox.frag");

    this->matricesUbo = std::make_unique<UniformBuffer>(2 * mat4Size_bytes);
    this->defaultShader->setUniformBlockBinding(matricesUboName, this->matricesUbo->getBindingPoint());
    this->skyboxShader->setUniformBlockBinding(matricesUboName, this->matricesUbo->getBindingPoint());

    // Setup camera
    this->cam = std::make_unique<Camera>(45.0f, static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
                                         0.1f, 1000.0f);

    // Setup directional light
    this->directionalLight = std::make_unique<DirectionalLight>(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 500.0f);
    this->directionalLight->setPosition({-10.0f, -10.0f, 100.0f})
            .setLookAtPoint(glm::vec3(0.0f));
}

void Game::init() {
    glEnable(GL_DEPTH_TEST);
}

void Game::loadWorld() {}

void Game::startGameLoop() {
    while (!glfwWindowShouldClose(this->window.get())) {
        // Calculate update duration
        auto currentUpdateTime = std::chrono::system_clock::now();
        auto updateDuration = currentUpdateTime - this->lastUpdateTime;
        this->lastUpdateTime = currentUpdateTime;

        this->update(updateDuration);
        this->render();

        glfwSwapBuffers(this->window.get());
        glfwPollEvents();
    }
}

void Game::update(std::chrono::duration<float> updateDuration) {
    this->cam->onUpdate(updateDuration);

    for (auto &gameObject : this->worldList) {
        gameObject->onUpdate(updateDuration);
    }
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto viewMatrix = this->cam->getViewMatrix();
    this->matricesUbo->bufferSubData(0, mat4Size_bytes, glm::value_ptr(viewMatrix))
            .bufferSubData(mat4Size_bytes, mat4Size_bytes, glm::value_ptr(this->cam->getProjectionMatrix()));

    this->defaultShader->use();
    for (auto &gameObject : this->worldList) {
        gameObject->render(this->defaultShader.get());
    }

    if (this->skybox) {
        glDepthFunc(GL_LEQUAL);
        this->matricesUbo->bufferSubData(0, mat4Size_bytes, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));
        this->skyboxShader->use();
        this->skybox->render(this->skyboxShader.get());
        glDepthFunc(GL_LESS);
    }
}

void Game::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    this->frameBufferWidth = width;
    this->frameBufferHeight = height;
    glViewport(0, 0, width, height);
    this->cam->setAspectRatioWidthToHeight(static_cast<float>(width) / height);
}

void Game::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window.get(), true);
    }

    this->cam->keyCallback(window, key, action, mods);
}

void Game::cursorPositionCallback(GLFWwindow *window, double x, double y) {
    this->cam->cursorPositionCallback(window, x, y);
}

void Game::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    this->cam->scrollCallback(window, xOffset, yOffset);
}

GLFWwindow* Game::getWindow() {return this->window.get();}

void Game::bindMatricesUbo(ShaderProgram *shader) {
    shader->setUniformBlockBinding(matricesUboName, this->matricesUbo->getBindingPoint());
}

void Game::pushBackInWorldList(std::shared_ptr<GameObject> gameObject) {
    this->worldList.push_back(std::move(gameObject));
}

void Game::setCam(std::unique_ptr<Camera> cam) {
    this->cam = std::move(cam);
}

Camera* Game::getCam() {return this->cam.get();}

void Game::setSkybox(std::unique_ptr<Skybox> skybox) {
    this->skybox = std::move(skybox);
}

void Game::setDirectionalLight(std::unique_ptr<DirectionalLight> directionalLight) {
    this->directionalLight = std::move(directionalLight);
}

DirectionalLight* Game::getDirectionalLight() {return this->directionalLight.get();}

} // namespace ge
