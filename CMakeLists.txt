cmake_minimum_required(VERSION 3.15)

set(ProjectName "TetrisBot")
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)

find_package(osmanip)


add_executable(${ProjectName} 
    main.cpp 
    piece.cpp 
    field.cpp 
    drawer.cpp 
    tetris.cpp
    bot.cpp
)

target_link_libraries(${ProjectName} osmanip::osmanip)

# # Добавляем поддержку библиотеки OpenMP
# find_package(OpenMP REQUIRED)
# if(NOT OpenMP_CXX_FOUND)
# 	message(SEND_ERROR "Failed to find OpenMP.")
# 	return()
# else()
# 	include_directories(${OpenMP_INCLUDE_DIRS})
#     message("OpenMP FOUND dir is ${OpenMP_INCLUDE_DIRS}.")
# endif()
# # Дополнительный флаг, необходим для функционирования библиотеки
# set(CMAKE_CXX_FLAGS "-fopenmp") 

# # Указание подключаемых библиотек
# target_link_libraries(${ProjectName} OpenMP::OpenMP_CXX)


# find_package(OpenMP REQUIRED)
# if(OPENMP_FOUND)
#     message("OPENMP FOUND")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
# endif()
# target_link_libraries(${ProjectName} OpenMP::OpenMP_CXX)
# set(CMAKE_CXX_FLAGS "-fopenmp") 


# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
# endif()
# # For CMake < 3.9, we need to make the target ourselves
# if(NOT TARGET OpenMP::OpenMP_CXX)
#     find_package(Threads REQUIRED)
#     add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
#     set_property(TARGET OpenMP::OpenMP_CXX
#                  PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
#     # Only works if the same flag is passed to the linker; use CMake 3.9+ otherwise (Intel, AppleClang)
#     set_property(TARGET OpenMP::OpenMP_CXX
#                  PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} Threads::Threads)

# endif()
# target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)



# cmake_minimum_required(VERSION 3.10)
# project(MyProject)
# find_package(OpenCV REQUIRED)
# add_executable(MyProject tutorial.cpp)
# target_link_libraries(MyProject ${OpenCV_LIBS})


# # Укажите путь к библиотеке и заголовочным файлам OpenMP
# set(OpenMP_C_FLAGS "-Xclang -fopenmp")
# set(OpenMP_C_LIB_NAMES "omp")
# set(OpenMP_omp_LIBRARY /opt/libomp/lib/libomp.dylib)
# set(OpenMP_omp_INCLUDE_DIR /opt/libomp/include)

# # Добавьте флаги и библиотеку OpenMP
# add_executable(MyProject testing.cpp)
# target_compile_options(MyProject PRIVATE ${OpenMP_C_FLAGS})
# target_include_directories(MyProject PRIVATE ${OpenMP_omp_INCLUDE_DIR})
# target_link_libraries(MyProject PRIVATE ${OpenMP_omp_LIBRARY})
