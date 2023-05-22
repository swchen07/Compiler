%{
#include "AST.hpp"

int yylex();

void yyerror(const char *s) {
    std::printf("Error: %s", s);
}

using namespace std;

%}

%union {
    std::string string;
    int intVal;
}

%token ASSIGN
%token IDENTIFIER
%token INT

%start STMT

%%

STMT: IDENTIFIER ASSIGN INT {$$ = new ASSIGNAST($1, $3);}


%%
