cmake_minimum_required(VERSION 3.1)

project(ez_plot C CXX)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(ez_plot
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_library(plotter
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plotter.cpp
)

set_target_properties(plotter PROPERTIES PUBLIC_HEADER 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/plotter.hpp
)

target_include_directories(plotter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_include_directories(ez_plot PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(ez_plot LINK_PUBLIC plotter)