cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(lab1)
add_executable(proga source/main.cpp)

add_subdirectory(matrix/)
add_subdirectory(tests/)

target_link_libraries(proga PUBLIC matrix)
target_link_libraries(proga PUBLIC test)
