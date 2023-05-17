%{
#include "AST.hpp"


int yylex();


void yyerror(const char *s) {
    printf("ERROR: %sn", s);
}


%}
%union {
    std::string *string;
    int token;
}


%token<string> IDENTIFIER
%token<token> 

%token INT CHAR BOOL VOID
%token RETURN CONTINUE BREAK
%token IF ELSE
%token FOR WHILE

%%


%%