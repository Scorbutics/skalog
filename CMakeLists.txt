cmake_minimum_required(VERSION 3.9)
project(skalog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
file(GLOB_RECURSE SOURCES
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.h
    *.cpp
)

string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" SOURCES "${SOURCES}")

set(SKA_DEBUG_DIR "Debug")
set(SKA_RELEASE_DIR "Release")

add_library(skalog STATIC ${SOURCES})
set_target_properties(skalog PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${SKA_DEBUG_DIR}
	      	ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${SKA_DEBUG_DIR}
        	ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${SKA_RELEASE_DIR})
