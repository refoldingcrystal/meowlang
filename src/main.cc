#include <iostream>
#include <string>
#include <vector>

#include "colors.h"
#include "helper.h"
#include "lexer.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Token> tokens = tokenizeFile(filename);

    if (!tokens.empty()) {
        std::cout << GREEN << "=> file tokenized correctly\n"
                  << RESET;
        // printTokens(tokens, filename);
    } else {
        std::cout << RED << "==> no tokens generated or file could not be opened\n"
                  << RESET;
        return 1;
    }

    // continue only if no errors detected while lexing
    bool passedLexing = true;
    for (const auto& token : tokens) {
        if (token.type == ERROR) {
            std::cout << RED << "=> error detected [" << token.line << ":" << token.column << "]\n"
                      << RESET << token.text << "\n";
            passedLexing = false;
        }
    }
    if (passedLexing && tokens.back().type == ENDOF) {
        std::cout << GREEN << "=> lexing finished without errors\n"
                  << RESET;
    } else {
        std::cout << RED << "=> lexing finished with errors, aborting\n"
                  << RESET;
        return 1;
    }



    return 0;
}
