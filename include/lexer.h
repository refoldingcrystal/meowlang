#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    ENDOF,
    ERROR,
    COMMENT,
    NUMBER,
    STRING,
    IDENTIFIER,

    PRINT,
    INPUT,
    IF,
    WHILE,
    THEN,
    END,
    LET,

    EQ,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    LPAREN,
    RPAREN,
    
    SEMICOLON,
    COLON,
    DOT,
    HASH,
    
    EQEQ,
    NOTEQ,
    LT,
    LTEQ,
    GT,
    GTEQ
};

struct Token {
    TokenType type;
    std::string text;
    int line, column;

    Token(TokenType type, std::string text, int line, int column)
        : type(type), text(std::move(text)), line(line), column(column) {}
};

std::string genErrorMsg(const std::string& line, const std::string& msg, const int& column);
std::vector<Token> tokenizeFile(const std::string& filename);

#endif