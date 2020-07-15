add_library(apple INTERFACE)
target_link_libraries(
    apple
    INTERFACE
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
) 