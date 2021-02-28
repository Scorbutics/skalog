cmake_minimum_required(VERSION 3.9)
project(skalog)

include_directories(../external/rlutil)

file(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)

string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" SOURCES "${SOURCES}")

add_library(skalog ${SOURCES})
set_property(TARGET skalog PROPERTY POSITION_INDEPENDENT_CODE ON)
