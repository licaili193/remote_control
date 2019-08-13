cmake_minimum_required(VERSION 3.1.0)

project(test_pattern_generation)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(pattern_generation_test
    pattern_generation_test.cpp
)

target_link_libraries(pattern_generation_test 
    ${OpenCV_LIBS}
)