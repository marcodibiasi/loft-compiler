cmake_minimum_required(VERSION 3.10)
project(Loft)

set(CMAKE_CXX_STANDARD 17)

# Directories
include_directories(
    src/ast
    src/lexer
    src/parser
)

# Source
set(SOURCES
    src/main.cpp
    src/ast/ast.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
)

add_executable(loft ${SOURCES})
