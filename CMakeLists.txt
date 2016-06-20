cmake_minimum_required(VERSION 2.8)
project(kmeans)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/point.cpp src/kmeans.cpp)

add_library(kmeans_lib ${SOURCE_FILES})

add_executable(kmeans src/main.cpp)
target_link_libraries(kmeans kmeans_lib)

add_subdirectory(gtest)
add_subdirectory(src/test)
