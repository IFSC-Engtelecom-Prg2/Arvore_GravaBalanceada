cmake_minimum_required(VERSION 3.14)
project(Prog)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(googletest/include googletest .)

add_executable(runTest test.cpp questao.h questao.cpp)

target_link_libraries(runTest gtest gtest_main -L${CMAKE_SOURCE_DIR}/libs prglib)
