cmake_minimum_required(VERSION 3.0.0...3.27.0)

aux_source_directory(. SRC)
add_library(fizz_buzz_lib STATIC ${SRC})
