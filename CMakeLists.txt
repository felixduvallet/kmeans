cmake_minimum_required(VERSION 2.8)
project(kmeans)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)

set(SOURCE_FILES
        src/point.cpp
        src/point.h
        src/kmeans.cpp
        src/kmeans.h)

add_library(kmeans_lib ${SOURCE_FILES})

add_executable(kmeans src/main.cpp)
target_link_libraries(kmeans kmeans_lib)

configure_file(src/sample_data/data_200_2.txt data_200_2.txt COPYONLY)
configure_file(src/sample_data/data_400_50.txt data_400_50.txt COPYONLY)


enable_testing()
add_subdirectory(googletest)
add_subdirectory(src/test)
