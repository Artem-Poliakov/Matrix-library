cmake_minimum_required(VERSION 3.10)

project(lab1)
add_executable(proga source/main.cpp)
add_subdirectory(matrix/)
target_link_libraries(proga PUBLIC matrix)