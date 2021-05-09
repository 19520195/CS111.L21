#include "lexer/lexer.hh"
#include "parser/parser.hh"

#include <iostream>

int main(const int argc, const char** argv) {
    std::cout << "Barebone 0.0.1\n";
    parser parser(std::unique_ptr<lexer>(new lexer));
    while (true) {
        std::cout << ">>> ";
        std::cout.flush();
        parser.parse();
    }

    return EXIT_SUCCESS;
}
