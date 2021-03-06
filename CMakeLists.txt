cmake_minimum_required(VERSION 3.5...3.10)
project(game_engine)

find_package(OpenGL REQUIRED)

add_subdirectory(extern)

add_library(${PROJECT_NAME}
    "src/Camera.cpp"
    "src/CameraFPV.cpp"
    "src/CameraNav.cpp"
    "src/DirectionalLight.cpp"
    "src/Game.cpp"
    "src/GameObject.cpp"
    "src/InstancingGameObjects.cpp"
    "src/InstancingMesh.cpp"
    "src/Light.cpp"
    "src/Mesh.cpp"
    "src/Model.cpp"
    "src/PointLight.cpp"
    "src/Quad.cpp"
    "src/ShaderProgram.cpp"
    "src/Skybox.cpp"
    "src/Texture2D.cpp"
    "src/UniformBuffer.cpp"
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glad
        glfw
        glm
    PRIVATE
        assimp
        stb::stb
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_constexpr
        cxx_noexcept
        cxx_nullptr
        cxx_override
        cxx_uniform_initialization
    PRIVATE
        cxx_auto_type
        cxx_generic_lambdas
        cxx_range_for
)

add_subdirectory(apps)
