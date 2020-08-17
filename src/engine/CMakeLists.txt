cmake_minimum_required(VERSION 3.17)

add_library(
    engine
    AABB.cpp
    window.cpp
    movable.cpp
    mesh.cpp
    shader.cpp
    object.cpp
    texture.cpp
    camera.cpp
    utils.cpp
    renderable.cpp
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
target_link_libraries(
    engine
    PUBLIC
    tinyobjloader
)
target_link_libraries(
    engine
    PRIVATE
    stb
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