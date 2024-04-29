cmake_minimum_required(VERSION 3.15)

set(ProjectName "TetrisBot")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)

find_package(osmanip)

add_executable(${ProjectName} main.cpp piece.cpp field.cpp drawer.cpp)

target_link_libraries(${ProjectName} osmanip::osmanip)

