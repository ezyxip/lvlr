cmake_minimum_required(VERSION 3.30)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_C_COMPILER "gcc" )


project(lvlr)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES "src/cpp/*.cpp")

include_directories(src/h/)

add_subdirectory(CLI11/)
add_subdirectory(portaudio/)
add_subdirectory(libsndfile/)

add_executable(lvlr_prj ${SOURCES})

target_link_libraries(lvlr_prj CLI11::CLI11)
target_link_libraries(lvlr_prj PortAudio)
target_link_libraries(lvlr_prj SndFile::sndfile)