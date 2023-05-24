#include <iostream>
#include <fstream>
#include <exception>
#include "AST.hpp"
#include "IRGenerator.hpp"

extern int yyparse();
BaseAST* Root;

int main(int argc, const char* argv[]) {
    std::string inputfile = argv[1]; 
    freopen(inputfile.c_str(), "r", stdin);

    yyparse();
    //Generating code
    IRGenerator Gen;
    Gen.GenerateCode(Root);

    Gen.GenObjectCode("simpledemo");

    std::cout << "Hello" << std::endl;

    return 0;
}