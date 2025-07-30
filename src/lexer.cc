#include "lexer.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

static std::map<std::string, TokenType> keywords = {
    {"print", PRINT},
    {"input", INPUT},
    {"if", IF},
    {"while", WHILE},
    {"then", THEN},
    {"end", END},
    {"let", LET}};

std::string genErrorMsg(const std::string& line, const std::string& msg, const int& column){
    std::string errorMsg = line + "\n";
    for (int i=0; i<column; i++) errorMsg += " ";
    errorMsg += "^= " + msg;
    return errorMsg;
}

std::vector<Token> tokenizeFile(const std::string& filename) {
    std::vector<Token> tokens;
    std::ifstream file(filename);

    if (!file.is_open()) {
        return tokens;
    }

    std::string line;
    int currentLine = 0;

    while (std::getline(file, line)) {
        currentLine++;
        std::string::size_type currentPos = 0;

        while (currentPos < line.length()) {
            char currentChar = line[currentPos];

            if (std::isspace(currentChar)) {
                currentPos++;
                continue;
            }

            if (currentChar == '#') {
                int startCol = currentPos;
                std::string commentText = line.substr(currentPos);
                tokens.emplace_back(COMMENT, commentText, currentLine, startCol + 1);
                currentPos = line.length();
                continue;
            }

            if (std::isdigit(currentChar)) {
                std::string numStr;
                int startCol = currentPos;
                while (currentPos < line.length() && std::isdigit(line[currentPos])) {
                    numStr += line[currentPos];
                    currentPos++;
                }
                tokens.emplace_back(NUMBER, numStr, currentLine, startCol + 1);
                continue;
            }

            if (std::isalpha(currentChar) || currentChar == '_') {
                std::string identStr;
                int startCol = currentPos;
                while (currentPos < line.length() && (std::isalnum(line[currentPos]) || line[currentPos] == '_')) {
                    identStr += line[currentPos];
                    currentPos++;
                }

                if (keywords.count(identStr)) {
                    tokens.emplace_back(keywords[identStr], identStr, currentLine, startCol + 1);
                } else {
                    tokens.emplace_back(IDENTIFIER, identStr, currentLine, startCol + 1);
                }
                continue;
            }

            if (currentChar == '"') {
                std::string stringLiteral;
                int startCol = currentPos;
                currentPos++;
                while (currentPos < line.length() && line[currentPos] != '"') {
                    stringLiteral += line[currentPos];
                    currentPos++;
                }
                if (currentPos < line.length() && line[currentPos] == '"') {
                    currentPos++;
                    tokens.emplace_back(STRING, stringLiteral, currentLine, startCol + 1);
                } else {
                    std::string errorMsg = genErrorMsg(line, "unclosed string literal: \"" + stringLiteral, startCol);
                    tokens.emplace_back(ERROR, errorMsg, currentLine, startCol + 1);
                    currentPos = line.length();
                }
                continue;
            }

            if (currentChar == '=') {
                int startCol = currentPos;
                if (currentPos + 1 < line.length() && line[currentPos + 1] == '=') {
                    tokens.emplace_back(EQEQ, "==", currentLine, startCol + 1);
                    currentPos += 2;
                } else {
                    tokens.emplace_back(EQ, "=", currentLine, startCol + 1);
                    currentPos++;
                }
                continue;
            }
            if (currentChar == '!') {
                int startCol = currentPos;
                if (currentPos + 1 < line.length() && line[currentPos + 1] == '=') {
                    tokens.emplace_back(NOTEQ, "!=", currentLine, startCol + 1);
                    currentPos += 2;
                } else {
                    std::string errorMsg = genErrorMsg(line, "unexpected character after '!'", startCol);
                    tokens.emplace_back(ERROR, errorMsg, currentLine, startCol + 1);
                    currentPos++;
                }
                continue;
            }
            if (currentChar == '<') {
                int startCol = currentPos;
                if (currentPos + 1 < line.length() && line[currentPos + 1] == '=') {
                    tokens.emplace_back(LTEQ, "<=", currentLine, startCol + 1);
                    currentPos += 2;
                } else {
                    tokens.emplace_back(LT, "<", currentLine, startCol + 1);
                    currentPos++;
                }
                continue;
            }
            if (currentChar == '>') {
                int startCol = currentPos;
                if (currentPos + 1 < line.length() && line[currentPos + 1] == '=') {
                    tokens.emplace_back(GTEQ, ">=", currentLine, startCol + 1);
                    currentPos += 2;
                } else {
                    tokens.emplace_back(GT, ">", currentLine, startCol + 1);
                    currentPos++;
                }
                continue;
            }

            int startCol = currentPos;
            switch (currentChar) {
                case '+':
                    tokens.emplace_back(PLUS, "+", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '-':
                    tokens.emplace_back(MINUS, "-", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '*':
                    tokens.emplace_back(ASTERISK, "*", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '/':
                    tokens.emplace_back(SLASH, "/", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '(':
                    tokens.emplace_back(LPAREN, "(", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case ')':
                    tokens.emplace_back(RPAREN, ")", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case ';':
                    tokens.emplace_back(SEMICOLON, ";", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case ':':
                    tokens.emplace_back(COLON, ":", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '.':
                    tokens.emplace_back(DOT, ".", currentLine, startCol + 1);
                    currentPos++;
                    break;
                case '#':
                    tokens.emplace_back(HASH, "#", currentLine, startCol + 1);
                    currentPos++;
                    break;
                default:
                    std::string errorMsg = "unexpected character: ";
                    errorMsg += currentChar;
                    errorMsg = genErrorMsg(line, errorMsg, startCol);
                    tokens.emplace_back(ERROR, errorMsg, currentLine, startCol + 1);
                    currentPos++;
                    break;
            }
        }
    }

    tokens.emplace_back(ENDOF, "EOF", currentLine + 1, 1);
    return tokens;
}