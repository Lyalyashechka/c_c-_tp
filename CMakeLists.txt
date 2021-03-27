cmake_minimum_required(VERSION 3.8)
project(transposition_matrix)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
SET(MYCOMPILE_FLAGS "-std=c11")
set(LIB_SOURCE_FILES project/src/creating_matrix.c project/src/transposition_consistant.c)
add_library(study_std_lib STATIC ${LIB_SOURCE_FILES})
include_directories(project/include)
add_executable(prog
    project/include/creating_matrix.h
    project/include/transposition_consistant.h
    project/src/main.c)
target_link_libraries(prog study_std_lib)

