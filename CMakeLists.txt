cmake_minimum_required(VERSION 3.5)
project(kmeans)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp point.cpp kmeans.cpp)
set(INCLUDE_DIRS .)

add_library(kmeans_lib ${SOURCE_FILES})

add_executable(kmeans main.cpp)
target_link_libraries(kmeans kmeans_lib)

add_subdirectory(gtest)
add_subdirectory(test)
