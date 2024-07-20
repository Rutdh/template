cmake_minimum_required(VERSION 3.0.0...3.27.0)
set(GTest_DIR "${CMAKE_SOURCE_DIR}\\sdk\\vcpkg\\installed\\x64-windows\\share\\gtest")

enable_testing()

aux_source_directory(. SRC)
add_executable(test_demo ${SRC})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_demo PRIVATE GTest::gtest GTest::gtest_main fizz_buzz_lib)
target_include_directories(test_demo PRIVATE "../src")

add_test(AllTestsInMain test_demo)

