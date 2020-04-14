#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game_engine/Camera.h>
#include <game_engine/DirectionalLight.h>
#include <game_engine/GameObject.h>
#include <game_engine/UniformBuffer.h>
#include <game_engine/ShaderProgram.h>
#include <game_engine/Skybox.h>

namespace ge {

///
/// \brief The Game class is a template for making a game. It sets up OpenGL and
/// runs a game loop providing default rendering behavior. In order to work with
/// GLFW callbacks, there should be a single global Game instance that is then
/// created in main().
///
class Game {
public:
    /// \name Global settings
    /// These settings should be adjusted prior to instantiating Game.
    ///@{
    static int glContextMajorVersion;
    static int glContextMinorVersion;

    static std::string baseProjectPath; ///< All subdirs are relative to this path.
    static std::string shadersDir;
    static std::string modelsDir;
    static std::string skyboxesDir;
    static std::string imagesDir;
    ///@}

    ///
    /// \brief New Builds an instance of game. This function should be provided for each
    ///            subclass of game.
    /// \param windowWidth Window width in screen coordinates.
    /// \param windowHeight Window height in screen coordinates.
    /// \param windowTitle Title of window.
    /// \return New Game instance that is initialized and loaded.
    ///
    static std::unique_ptr<Game> New(unsigned int windowWidth, unsigned int windowHeight,
                                     const std::string &windowTitle);
    virtual ~Game() = default;

    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game& operator=(const Game &) = delete;
    Game& operator=(Game &&) = delete;

    ///
    /// \brief startGameLoop Starts the game loop until user presses 'ESC'
    ///
    void startGameLoop();

    /// \name GLFW callbacks
    /// Callbacks to be hooked up to GLFW callback functions
    ///@{
    void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
    virtual void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    virtual void cursorPositionCallback(GLFWwindow *window, double x, double y);
    virtual void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    virtual void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
    ///@}

    GLFWwindow* getWindow();

protected:
    Game(unsigned int windowWidth, unsigned int windowHeight, const std::string &windowTitle);

    ///
    /// \brief init Configure global states for OpenGL, GLFW, etc.
    ///
    /// Default behavior enables depth testing.
    ///
    virtual void init();

    ///
    /// \brief loadWorld Load all game objects in this function.
    ///
    virtual void loadWorld();

    ///
    /// \brief bindMatricesUbo Binds shaders to UBO for view and projection matrices.
    /// \param shader Shader to bind.
    ///
    void bindMatricesUbo(ShaderProgram *shader);

    ///
    /// \brief pushBackInWorldList Pushes game object into world list to allow
    ///                            updating and rendering during the game loop.
    /// \param gameObject Game object to push into the world list.
    ///
    void pushBackInWorldList(std::shared_ptr<GameObject> gameObject);

    void setCam(std::unique_ptr<Camera> cam);
    Camera* getCam();

    void setSkybox(std::unique_ptr<Skybox> skybox);

    void setDirectionalLight(std::unique_ptr<DirectionalLight> directionalLight);
    DirectionalLight* getDirectionalLight();

    int getFrameBufferWidth() const;
    int getFrameBufferHeight() const;

private:
    ///
    /// \brief update Updates all game objects.
    /// \param updateDuration Duration since the last frame.
    ///
    virtual void update(std::chrono::duration<float> updateDuration);

    ///
    /// \brief render Renders all game objects using the default shaders.
    ///
    virtual void render();

    using WindowPtr = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>;

    WindowPtr window;
    int frameBufferWidth, frameBufferHeight;

    std::chrono::system_clock::time_point lastUpdateTime;

    std::unique_ptr<ShaderProgram> defaultShader;
    std::unique_ptr<ShaderProgram> skyboxShader;
    std::unique_ptr<UniformBuffer> matricesUbo;

    std::unique_ptr<Camera> cam;

    ///
    /// \brief worldList Container of all game objects to be updated and rendered
    /// during each frame in the game loop.
    ///
    std::vector<std::shared_ptr<GameObject>> worldList;

    std::unique_ptr<Skybox> skybox;

    std::unique_ptr<DirectionalLight> directionalLight;
};

inline int Game::getFrameBufferWidth() const {return this->frameBufferWidth;}
inline int Game::getFrameBufferHeight() const {return this->frameBufferHeight;}

} // namespace ge
