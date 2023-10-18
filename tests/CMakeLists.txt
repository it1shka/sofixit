cmake_minimum_required(VERSION 3.23)
project(sofixit_tests)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(sofixit_tests function_tests.cpp)
target_link_libraries(sofixit_tests PRIVATE sofixit)
