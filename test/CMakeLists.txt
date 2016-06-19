cmake_minimum_required(VERSION 2.8)

# CMake file for finding all unit tests contained inside any .cc file in this
# directory. This also installs the unit test binary inside build/test.

# Set the test name here. Nothing else should have to change if this file is
# copied to a new module.
set(TEST_NAME kmeans_tests)

########################################
enable_testing()
set(TEST_SRC_FILES
        test_point.cpp)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})
target_link_libraries(${TEST_NAME}
        kmeans_lib
        gtest gtest_main pthread)

# Run "make test" to make sure all tests pass.
add_test(
  NAME ${TEST_NAME}
  COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_NAME}
)

# Install unit test in build/test directory.
install(TARGETS ${TEST_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/test")
