project(example_game)

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    "src/ExampleGame.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    game_engine::game_engine
)

target_compile_features(${PROJECT_NAME} PRIVATE
    cxx_auto_type
    cxx_constexpr
    cxx_generic_lambdas
    cxx_override
    cxx_nullptr
    cxx_range_for
)

file(COPY
        "${CMAKE_CURRENT_SOURCE_DIR}/images"
        "${CMAKE_CURRENT_SOURCE_DIR}/models"
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "${CMAKE_CURRENT_SOURCE_DIR}/skyboxes"
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
