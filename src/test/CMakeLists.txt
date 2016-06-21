cmake_minimum_required(VERSION 2.8)

# CMake file for finding all unit tests contained inside any .cc file in this
# directory. This also installs the unit test binary inside build/test.

# Set the test name here. Nothing else should have to change if this file is
# copied to a new module.
set(TEST_NAME kmeans_tests)

########################################
enable_testing()
set(TEST_SRC_FILES
        test_point.cpp
        test_data_loading.cpp
        test_end_to_end.cpp
        test_main.cpp)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

include_directories(${PROJECT_SOURCE_DIR}/googletest
        ${PROJECT_SOURCE_DIR}/googletest/include)

target_link_libraries(${TEST_NAME}
        kmeans_lib
        gtest gtest_main pthread)

# Run "make test" to make sure all tests pass.
add_test(
        NAME ${TEST_NAME}
        COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_NAME}
)
configure_file(test_data_3.txt test_data_3.txt COPYONLY)
configure_file(../sample_data/data_200_2.txt data_200_2.txt COPYONLY)

# Install unit test in build/test directory.
install(TARGETS ${TEST_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/test")
