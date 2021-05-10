#include <src/lexer/lexer.hh>
#include <src/parser/parser.hh>

#include <iostream>

int main(const int argc, const char** argv) {
    std::cout << "Barebone 0.1\n";
    parser parser(std::make_unique<lexer>(lexer()));
    while (true) {
        std::cout << ">>> ";
        std::cout.flush();
        parser.live_parse();
    }

    return EXIT_SUCCESS;
}
