#ifndef HELPER_H
#define HELPER_H

#include <string>

#include "lexer.h"

void printTokens(const std::vector<Token>& tokens, const std::string& filename);
std::string getTokenTypeString(TokenType type);

#endif