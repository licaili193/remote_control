cmake_minimum_required(VERSION 3.1.0)

project(test_pattern_generation)

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(test_pattern_generator
    TestPatternGenerator.cpp
)
target_link_libraries(test_pattern_generator 
    ${OpenCV_LIBS}
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(pattern_generation_test
    pattern_generation_test.cpp
)
target_link_libraries(pattern_generation_test 
    test_pattern_generator
)