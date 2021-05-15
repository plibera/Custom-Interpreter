cmake_minimum_required(VERSION 3.10)

project(Projekt_TKOM)

set(CMAKE_CXX_STANDARD 17)
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
    src/main.cpp
)

add_executable(testTkom
    test/test.cpp
    src/token.cpp
    src/source.cpp
    src/lexer.cpp
)

target_link_libraries(testTkom PRIVATE gtest)
