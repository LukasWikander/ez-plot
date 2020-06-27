cmake_minimum_required(VERSION 3.1)

project(ez-plot)

add_library(plotter
    src/plotter.cpp
)

add_executable(ez-plot
    src/main.cpp
)

target_include_directories(ez-plot PUBLIC
    <BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
)