cmake_minimum_required(VERSION 3.10)
project(Loft)

set(CMAKE_CXX_STANDARD 17)

# Directories
include_directories(
    src/lexer
)

# Source
set(SOURCES
    src/main.cpp
    src/lexer/lexer.cpp
)

add_executable(loft ${SOURCES})
