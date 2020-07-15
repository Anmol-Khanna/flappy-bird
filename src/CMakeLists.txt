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
target_link_libraries(
    main
    PRIVATE
    engine
    assimp
)


