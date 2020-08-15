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

add_executable(main main.cpp)
add_library(fractal "${CMAKE_CURRENT_LIST_DIR}/fractal/fractal.cpp")
target_include_directories(
    fractal
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/fractal/"
)
target_link_libraries(
    fractal
    PRIVATE
    engine
)
target_link_libraries(
    main
    PRIVATE
    fractal
    engine
)
