cmake_minimum_required(VERSION 3.10)

project(test)
add_library(test source/tests.cpp)
target_include_directories(test PUBLIC include/)
target_link_libraries(test PUBLIC matrix)
