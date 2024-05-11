cmake_minimum_required(VERSION 3.15)

set(ProjectName "TetrisBot")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)

find_package(osmanip)
find_package(OpenMP)

add_executable(${ProjectName} 
    main.cpp 
    piece.cpp 
    field.cpp 
    drawer.cpp 
    tetris.cpp
    bot.cpp
)

target_link_libraries(${ProjectName} PUBLIC osmanip::osmanip OpenMP::OpenMP_CXX)
