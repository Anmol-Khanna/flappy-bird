cmake_minimum_required(VERSION 3.17)

add_library(
    engine
    window.cpp
    movable.cpp
    mesh.cpp
    shader.cpp
    player.cpp
    texture.cpp
)
target_include_directories(
    engine
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(
    engine
    PUBLIC
    glad
    glfw
    glm
)
if (USE_IMGUI)
    target_compile_definitions(
        engine
        PRIVATE
        USE_IMGUI=1
    )
    target_link_libraries(
        engine
        PRIVATE
        imgui
    )
endif()

target_compile_features(engine PUBLIC cxx_std_17)