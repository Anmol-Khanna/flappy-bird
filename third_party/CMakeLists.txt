add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
add_subdirectory(assimp)
set(BUILD_SHARED_LIBS ON)
set(STB_IMAGE ${EXTERNAL}/stb)
add_library(stb INTERFACE)
target_include_directories(
    stb
    INTERFACE
    ${STB_IMAGE}
)

if (USE_IMGUI)
    set(IMGUI ${EXTERNAL}/imgui)
    add_library(
        imgui
        ${IMGUI}/imgui.cpp
        ${IMGUI}/imgui_draw.cpp
        ${IMGUI}/imgui_widgets.cpp
        ${IMGUI}/examples/imgui_impl_opengl3.cpp
        ${IMGUI}/examples/imgui_impl_glfw.cpp
    )

    target_include_directories(
        imgui
        PUBLIC
        "${IMGUI}"
        "${IMGUI}/examples"
    )

    target_link_libraries(
        imgui
        PRIVATE
        glad
        glfw
    )
endif()