cmake_minimum_required(VERSION 3.10)

project(Projekt_TKOM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_executable(tkom 
    src/source.cpp
    src/lexer.cpp
    src/main.cpp
)