#pragma once
#include "lexer.h"

class Lexer; 

class Parser {
public:
    Parser(Lexer& l) : lexer(l) {} 

private: 
    Lexer& lexer;
};
