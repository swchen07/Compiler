

%{
#include <iostream>
#include <string>

int yylex();

void yyerror(const char *s) {
    std::printf("Error: %s", s);
}

using namespace std;

%}

%union {
    std::string *strVal;
    int token;
    int intVal;
    //BaseAST *astVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token ADD
%token LPAREN RPAREN LBRACE RBRACE
%token INT RETURN

%token <strVal> IDENTIFIER
%token <intVal> CONST_INT

// 非终结符的类型定义

%type <strVal> FuncDef FuncType Block Stmt
%type <intVal> Number

/* 优先级和结合性定义 */

%%

CompUnit
    : FuncDef                                   {printf("CompUnit");}
    ;

FuncDef
    : FuncType IDENTIFIER LPAREN RPAREN Block   {printf("FuncDef\n");}
    ;

Block
    : LBRACE Stmt RBRACE                        {printf("Block\n");}
    ;

FuncType
    : INT                                       {printf("FuncType\n");}
    ;

Stmt
    : RETURN Exp                                {printf("Stmt\n");}
    ;

Exp
    : Number ADD Number                         {printf("Exp\n");}
    ;

Number
    : CONST_INT                                 {printf("%d",$1);}
    ;

%%

int yywrap(){
    return 1;
}
int main()
{
    yyparse();
}
