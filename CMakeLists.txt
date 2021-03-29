cmake_minimum_required(VERSION 3.8)
project(transposition_matrix)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-pthread -fopenmp -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pthread -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
SET(MYCOMPILE_FLAGS "-std=c11")

include_directories(project/include)

add_library(transpose_naive STATIC
    project/src/creating_matrix.c
    project/src/transposition_consistant.c
    project/include/creating_matrix.h
    project/include/transposition_consistant.h)

add_library(transpose_parallel SHARED
    project/src/creating_matrix.c
    project/src/transposition_parallel.c
    project/include/creating_matrix.h
    project/include/transposition_parallel.h)


add_executable(naive
    project/src/main.c)

add_executable(parallel
    project/src/main.c)

add_executable(stress 
    project/src/stress_test.c)
target_link_libraries(naive transpose_naive)
target_link_libraries(parallel transpose_parallel)
target_link_libraries(stress dl transpose_naive transpose_parallel)

