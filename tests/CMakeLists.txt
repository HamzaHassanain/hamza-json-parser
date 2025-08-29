cmake_minimum_required(VERSION 3.10)

# Use FetchContent to download and add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Get source files for the library (excluding main app)
file(GLOB PARSER_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create a test executable
add_executable(json_parser_tests test.cpp ${PARSER_SRC_FILES})

# Include directories for headers
target_include_directories(json_parser_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}
)

# Link your test executable to the GTest libraries
target_link_libraries(json_parser_tests
  PRIVATE
    GTest::gtest_main
    GTest::gtest
)

# Set C++ standard
target_compile_features(json_parser_tests PRIVATE cxx_std_17)

# Tell CMake to find and register the tests to be run with CTest
include(GoogleTest)
gtest_discover_tests(json_parser_tests)