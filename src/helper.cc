#include "helper.h"

void printTokens(const std::vector<Token>& tokens, const std::string& filename) {
    std::cout << "tokens from file '" << filename << "':\n";
    for (const auto& token : tokens) {
        std::cout << "  [" << token.line << ":" << token.column
                  << "] \t" << getTokenTypeString(token.type);
        if (token.type != ERROR && token.type != COMMENT && token.type != ENDOF) {
            std::cout << "  » " << token.text << " «";
        }
        std::cout << "\033[0m\n";
    }
}

std::string getTokenTypeString(TokenType type) {
    switch (type) {
        case ENDOF:
            return "\033[32mENDOF";
        case ERROR:
            return "\033[31mERROR";
        case COMMENT:
            return "\033[34mCOMMENT";
        case NUMBER:
            return "NUMBER";
        case STRING:
            return "STRING";
        case IDENTIFIER:
            return "IDENTIFIER";
        case PRINT:
            return "PRINT";
        case INPUT:
            return "INPUT";
        case IF:
            return "IF";
        case WHILE:
            return "WHILE";
        case THEN:
            return "THEN";
        case END:
            return "END";
        case LET:
            return "LET";
        case EQ:
            return "EQ";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case ASTERISK:
            return "ASTERISK";
        case SLASH:
            return "SLASH";
        case LPAREN:
            return "LPAREN";
        case RPAREN:
            return "RPAREN";
        case SEMICOLON:
            return "SEMICOLON";
        case COLON:
            return "COLON";
        case DOT:
            return "DOT";
        case EQEQ:
            return "EQEQ";
        case NOTEQ:
            return "NOTEQ";
        case LT:
            return "LT";
        case LTEQ:
            return "LTEQ";
        case GT:
            return "GT";
        case GTEQ:
            return "GTEQ";
        default:
            return "UNKNOWN";
    }
}