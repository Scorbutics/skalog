cmake_minimum_required(VERSION 3.9)
project(skalog_bench)

include_directories(../src/src)
link_directories(../lib)

file(GLOB_RECURSE SOURCES
	src/*.h
	src/*.cpp
)

string(REGEX REPLACE "[^;]*CMakeFiles/[^;]+;?" "" SOURCES "${SOURCES}")

add_executable(skalog_bench ${SOURCES})
find_package(Threads REQUIRED)
target_link_libraries(skalog_bench skalog Threads::Threads)
