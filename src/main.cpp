#include <iostream>
#include <string>
#include <cstdlib>
#include "ast.h"
#include "lexer.h"

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Usage: ./loft <file>" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
