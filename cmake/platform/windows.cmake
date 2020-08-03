add_library(windows INTERFACE)
find_package(OpenGL REQUIRED)
target_link_libraries(
    windows
    INTERFACE
    ${OPENGL_LIBRARIES}
)
target_include_directories(
    windows
    INTERFACE
    ${OPENGL_INCLUDE_DIRS}
)