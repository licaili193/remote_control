cmake_minimum_required(VERSION 3.1.0)

project(test)

set(CMAKE_AUTOMOC TRUE)

find_package(Qt5Widgets REQUIRED)

add_executable(main
    main.cpp
    qblcanvas.cpp
)

target_link_libraries(main 
    Qt5::Widgets 
    Blend2D::Blend2D
)

qt5_use_modules(main 
    Widgets
)