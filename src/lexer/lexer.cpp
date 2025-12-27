#include <fstream>
#include "lexer.h"

bool Lexer::is_at_end() const {
    return pos >= source.size();
}

char Lexer::peek() const {
    if(is_at_end()) return '\0';
    return source[pos];
}

char Lexer::advance() {
    char c = peek();
    pos++;
    if(c == '\n') line++;
    
    return c;
}

void Lexer::skip_white_space(){
    while(!is_at_end() && isspace(peek())) advance();
}

Token Lexer::next_token(){
    skip_white_space();

    if(is_at_end()) 
        return Token{TokenType::END_OF_FILE, "", line};

    char c = peek();
    if(isalpha(c)) return read_identifier_or_keyword();
    if(isdigit(c)) return read_number();
    if(c == '|') return read_pattern();

    // SYMBOLS 

    if(c == '>'){
        advance();
        if(peek() == '>'){
            advance();
            return {TokenType::PLAY, ">>", line};
        }
        return {TokenType::ASSIGN_PATTERN, ">", line};
    }

    switch (c) {
        case '=': 
            advance();        
            return Token{TokenType::EQUALS, "=", line};
        case '@': 
            advance();        
            return Token{TokenType::AT, "@", line};
        case '(': 
            advance();        
            return Token{TokenType::L_PAREN, "(", line};
        case ')': 
            advance();        
            return Token{TokenType::R_PAREN, ")", line};
        case '[': 
            advance();        
            return Token{TokenType::L_BRACKET, "[", line};
        case ']': 
            advance();        
            return Token{TokenType::R_BRACKET, "]", line};
        case ':': 
            advance();        
            return Token{TokenType::COLON, ":", line};
        case '.': 
            advance();        
            return Token{TokenType::DOT, ".", line};
        case ',': 
            advance();        
            return Token{TokenType::COMMA, ",", line};
    }

    advance();
    return Token{TokenType::INVALID, "", line};
}

Token Lexer::read_identifier_or_keyword(){
    size_t start = pos;

    while(!is_at_end() && (isalnum(peek()) || peek() == '_'))
        advance();

    std::string word = source.substr(start, pos - start);

    // KEYWORDS
    if(word == "sound") return Token{TokenType::SOUND, word, line};
    if(word == "track") return Token{TokenType::TRACK, word, line};
    if(word == "par") return Token{TokenType::PAR, word, line};
    if(word == "section") return Token{TokenType::SECTION, word, line};
    if(word == "using") return Token{TokenType::USING, word, line};

    // IDENTIFIERS
    return Token{TokenType::IDENTIFIER, word, line};
}

Token Lexer::read_number(){
    size_t start = pos;
    bool has_dot = false;

    while(!is_at_end()){
        char c = peek();
        
        if(isdigit(c)) advance();
        else if(c == '.' && !has_dot) {
            has_dot = true;
            advance();
        }
        else break;
    }

    std::string word = source.substr(start, pos - start);
    return Token{TokenType::NUMBER, word, line};
}

Token Lexer::read_pattern(){
    size_t start = pos;

    while(!is_at_end() && (peek() == '|' || peek() == 'x' || peek() == 'o')) 
        advance();

    std::string word = source.substr(start, pos - start);
    return Token{TokenType::PATTERN, word, line};
}
