cmake_minimum_required(VERSION 3.5)
project(tp2-algo3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -pthread -std=gnu++11 -ggdb3 -g")

# Ejecutables
add_executable(ej1 ej1/ej1.cpp)
add_executable(ej2 ej2/ej2.cpp)
add_executable(ej3 ej3/ej3.cpp)
