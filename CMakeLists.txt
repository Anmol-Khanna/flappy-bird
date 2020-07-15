cmake_minimum_required(VERSION 3.17)

project(flappybird VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(PLATFORM ${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform)
set(EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(FLAPPYBIRD ${CMAKE_CURRENT_SOURCE_DIR})

option(USE_IMGUI "This enables the IMGUI window" ON)

if (APPLE)
    include(${PLATFORM}/apple.cmake)
elseif (WIN32)
    include(${PLATFORM}/windows.cmake)
endif(APPLE)

add_subdirectory(${EXTERNAL})
add_subdirectory(${FLAPPYBIRD}/src)
