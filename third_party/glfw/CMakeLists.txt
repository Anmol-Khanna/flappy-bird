cmake_minimum_required(VERSION 3.17)
project(glfw)

set(GLFW_LOCATION ${EXTERNAL}/glfw)
find_package(GLFW REQUIRED)

add_library(glfw INTERFACE)
target_include_directories(
    glfw
    INTERFACE 
    ${GLFW_INCLUDE_DIR}
)
target_link_libraries(
    glfw 
    INTERFACE 
    ${GLFW_LIBRARY}
)