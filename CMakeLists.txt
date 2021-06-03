cmake_minimum_required(VERSION 3.10)

project(Projekt_TKOM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(googletest)

include_directories(
    include
    googletest/include
)

add_executable(tkom 
    src/token.cpp
    src/source.cpp
    src/lexer.cpp
    src/parser.cpp
    src/main.cpp
    src/objects.cpp
    src/interpreter.cpp
)

add_executable(testTkom
    test/test.cpp
    src/token.cpp
    src/source.cpp
    src/lexer.cpp
    src/parser.cpp
    src/objects.cpp
    src/interpreter.cpp
)

target_link_libraries(testTkom PRIVATE gtest)
