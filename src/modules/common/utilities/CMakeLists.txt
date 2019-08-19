cmake_minimum_required(VERSION 3.1.0)

project(utilities)

add_subdirectory(test_pattern_generation)
add_subdirectory(image_preview)

add_executable(pattern_generation_test
    pattern_generation_test.cpp
)
target_link_libraries(pattern_generation_test 
    test_pattern_generator
    image_previewer

    ${CMAKE_THREAD_LIBS_INIT}
)
