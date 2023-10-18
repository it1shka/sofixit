cmake_minimum_required(VERSION 3.23)
project(sofixit)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(tests)

add_library(sofixit INTERFACE)
target_include_directories(sofixit INTERFACE solution)
