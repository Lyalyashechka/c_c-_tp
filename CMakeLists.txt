cmake_minimum_required(VERSION 3.8)
project(parabols)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
SET(MYCOMPILE_FLAGS "-std=c11")
set(LIB_SOURCE_FILES project/src/parab.c)
add_Library(study_std_lib STATIC ${LIB_SOURCE_FILES})
include_directories(project/include)
add_executable(prog
    project/include/parab.h  
    project/src/main.c)
target_link_libraries(prog study_std_lib)


enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(tests project/test/test.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests study_std_lib)


