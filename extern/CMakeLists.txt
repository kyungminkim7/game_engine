# assimp library for 3D model loading
OPTION(ASSIMP_BUILD_TESTS "If the test suite for Assimp is built in addition to the library." OFF)
OPTION(ASSIMP_INSTALL "Disable this if you want to use assimp as a submodule." OFF)
add_subdirectory(assimp)

# glad library
add_library(glad "glad/src/glad.c")

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/glad/include>
    $<INSTALL_INTERFACE:include>
)

# glfw library for windowing and OpenGL context creation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

# glm library for linear algebra
add_subdirectory(glm)

# STB library for loading image files
add_library(stb INTERFACE)
add_library(stb::stb ALIAS stb)

target_include_directories(stb INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/stb>
    $<ISTALL_INTERFACE:stb>
)
