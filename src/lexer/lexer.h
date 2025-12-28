#pragma once
#include <string>

enum class TokenType {
    // KEYWORDS
    SOUND,
    TRACK,
    PAR, 
    SECTION,
    MODULE,
    USING,

    // SYMBOLS
    EQUALS,         // =
    AT,             // @
    L_PAREN,        // (
    R_PAREN,        // )
    L_BRACKET,      // [
    R_BRACKET,      // ]
    COLON,          // :
    DOT,            // .
    COMMA,          // ,
    PIPE,           // |
    EXCLAMATION,    // !
    ASSIGN_PATTERN, // >
    PLAY,           // >>

    // OTHERS
    INVALID,
    NUMBER,
    PATTERN,
    IDENTIFIER,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string element;
    int line;
};

class Lexer {
public: 
    explicit Lexer(const std::string& src) : source(src) {}
    Token next_token();

    bool is_at_end() const;

private:
    const std::string& source;
    size_t pos = 0;
    int line = 1;

    char peek() const;
    char advance();
    void skip_white_space();

    Token read_identifier_or_keyword();
    Token read_number();
    Token read_pattern();
};
