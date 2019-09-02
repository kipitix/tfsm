cmake_minimum_required(VERSION 2.8)

project(tfsm)

set (CMAKE_CXX_STANDARD 11)

file(GLOB HDR *.h *.hpp)
file(GLOB SRC *.cpp)

add_executable(${PROJECT_NAME} ${HDR} ${SRC})
