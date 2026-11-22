#include "ast.hpp"
#include <iostream>

extern int yyparse();
extern std::shared_ptr<ProgramNode> root;

extern FILE* yyin;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./minic <source_file>\n";
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    std::cout << "Parsing file: " << argv[1] << "\n\n";

    int result = yyparse();

    fclose(yyin);

    if (result == 0 && root) {
        std::cout << "Parsing successful!\n\n";
        std::cout << "Abstract Syntax Tree:\n";

        root->print();
    } else {
        std::cerr << "Parsing failed!\n";
        return 1;
    }

    return 0;
}
