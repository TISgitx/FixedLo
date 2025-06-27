cmake_minimum_required(VERSION 3.10)
project(lomake)

set(CMAKE_CXX_STANDARD 17)

include_directories(core)

file(GLOB SOURCES "main.cpp" "src/*.cpp")

add_executable(lomake ${SOURCES})
