#include <iostream>
#include <fstream>
#include <exception>
#include "AST.hpp"
#include "IRGenerator.hpp"

extern int yyparse();
BaseAST* Root;

int main(int argc, const char* argv[]) {
    std::string inputfile = argv[1]; 

    // get module name
    int moduleleft = inputfile.rfind("/") + 1;
    int moduleright = inputfile.rfind(".");
    std::string modulename = inputfile.substr(moduleleft, moduleright-moduleleft);
    std::string modulename_path = inputfile.substr(0, moduleright);
    std::string newmodulename = "io/"+modulename+".temp.c";

    // micro
    system(("./build/microhandler "+inputfile+" "+newmodulename).c_str());

    freopen(newmodulename.c_str(), "r", stdin);

    // freopen(inputfile.c_str(), "r", stdin);

    yyparse();
    //Generating code
    IRGenerator Gen;
    Gen.GenerateCode(Root);

    Gen.GenObjectCode("io/"+modulename+".o");
    Gen.DumpIRCode("io/"+modulename+".ir");

    std::cout << "Compile Success!" << std::endl;

    return 0;
}