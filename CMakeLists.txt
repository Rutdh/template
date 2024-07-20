cmake_minimum_required(VERSION 3.0.0...3.27.0)
project(FizzBuzz VERSION 0.1.0 LANGUAGES C CXX)

add_executable(FizzBuzz main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

target_include_directories(FizzBuzz PRIVATE src)
target_link_libraries(FizzBuzz PRIVATE fizz_buzz_lib)