#cmake_minimum_required(VERSION 3.8)
#project(untitled)
#
#find_package(OpenMP REQUIRED)
#
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11 -fopenmp")
#
#add_executable(untitled task1.cpp)
#target_link_libraries(untitled PRIVATE OpenMP::OpenMP_C)

cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(Task1 task1.cpp
        task2.cpp
        task3.cpp
        task4.cpp
        task5.cpp)
target_compile_options(Task1 PRIVATE -Wall ${OpenMP_CXX_FLAGS})
target_link_libraries(Task1 PRIVATE ${OpenMP_CXX_FLAGS})
