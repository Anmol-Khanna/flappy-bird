cmake_minimum_required(VERSION 3.17)

add_subdirectory(engine)
if (APPLE)
    target_link_libraries(
        engine
        PRIVATE
        apple
    )
elseif (WIN32)
    target_link_libraries(
        engine
        PRIVATE
        windows
    )
endif()

add_library(tinyobjloader_wrapper tinyobjloader_wrapper.cpp)
target_include_directories(
    tinyobjloader_wrapper
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
)
target_link_libraries(
    tinyobjloader_wrapper
    PRIVATE
    stb
)
target_link_libraries(
    tinyobjloader_wrapper
    PUBLIC
    engine
    tinyobjloader
)
add_executable(main main.cpp)
target_link_libraries(
    main
    PRIVATE
    engine
    tinyobjloader_wrapper
)
