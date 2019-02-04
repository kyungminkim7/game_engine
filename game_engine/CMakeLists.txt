cmake_minimum_required(VERSION 3.0)
project(game_engine)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(${PROJECT_NAME} SHARED
    "src/Camera.cpp"
    "src/DirectionalLight.cpp"
    "src/GameObject.cpp"
    "src/InstancingGameObjects.cpp"
    "src/InstancingMesh.cpp"
    "src/Mesh.cpp"
    "src/Model.cpp"
    "src/PointLight.cpp"
    "src/ShaderProgram.cpp"
    "src/Texture2D.cpp"
    "src/UniformBuffer.cpp"
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glad
        glfw
        glm
    PRIVATE
        assimp
        stb
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
