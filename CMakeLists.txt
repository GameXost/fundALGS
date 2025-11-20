cmake_minimum_required(VERSION 3.10)
project(algosi C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(pak1)
add_subdirectory(pak2)
add_subdirectory(pak3)