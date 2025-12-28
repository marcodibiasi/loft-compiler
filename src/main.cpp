#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "ast.h"
#include "lexer.h"
#include "parser.h"

std::string file_to_string(const std::string& filename);

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Usage: ./loft <file>" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::string source = file_to_string(argv[1]);
    Lexer lexer(source);
    
    while(!lexer.is_at_end()) {
        Token tok = lexer.next_token();
        std::cout   << "Token: " << static_cast<int>(tok.type) << " - "
                    << "Element: " << tok.element << " - "
                    << "Line: " << tok.line 
                    << std::endl;
    }
    

    return EXIT_SUCCESS;
}

std::string file_to_string(const std::string& filename) {
    std::ifstream file(filename);

    if(!file.is_open())
        throw std::runtime_error("Error: cant open file" + filename);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
