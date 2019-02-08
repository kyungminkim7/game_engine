cmake_minimum_required(VERSION 3.0)

add_subdirectory(assimp)
add_subdirectory(glm)

# glad library
add_library(glad SHARED "glad/src/glad.c")

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/glad/include>
)

# STB library
add_library(stb INTERFACE)

target_include_directories(stb INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/stb>
)

add_subdirectory(game_engine)
