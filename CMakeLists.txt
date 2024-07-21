cmake_minimum_required(VERSION 3.30)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_C_COMPILER "gcc" )


project(lvlr)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "src/cpp/*.cpp")

include_directories(src/h/)

add_executable(lvlr_prj ${SOURCES})

