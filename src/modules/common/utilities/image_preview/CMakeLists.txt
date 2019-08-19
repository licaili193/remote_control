cmake_minimum_required(VERSION 3.1.0)

project(image_preview)

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(image_previewer
    ImagePreviewer.cpp
)
target_link_libraries(image_previewer 
    ${OpenCV_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
