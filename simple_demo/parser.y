%{
#include "AST.hpp"
#include <iostream>
#include <string>

int yylex(void);
BaseAST* Root; 

void yyerror(const char *s) {
    std::printf("Error: %s", s);
}

using namespace std;

%}

%output "parser.cpp"

%union {
    char* strVal;
    int token;
    int intVal;
    BaseAST *astVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token ADD
%token LPAREN RPAREN LBRACE RBRACE
%token RETURN

%token <strVal> IDENTIFIER INT
%token <intVal> CONST_INT

// 非终结符的类型定义

%type <astVal> FuncDef Block Stmt Exp CompUnit
%type <strVal> FuncType
%type <intVal> Number

/* 优先级和结合性定义 */

%%

CompUnit
    : FuncDef                                   {$$ = new ProgramAST((FunctionAST*)$1); Root = $$;}
    ;

FuncDef
    : FuncType IDENTIFIER LPAREN RPAREN Block   {$$ = new FunctionAST($1, $2, (BlockAST*)$5);}
    ;

Block
    : LBRACE Stmt RBRACE                        {$$ = new BlockAST((StmtAST*)$2);}
    ;

FuncType
    : INT                                       {$$ = $1;}
    ;

Stmt
    : RETURN Exp ';'                            {$$ = new StmtAST((ExprAST*)$2);}
    ;

Exp
    : Number ADD Number                         {$$ = new ExprAST($1, '+', $3);}
    ;

Number
    : CONST_INT                                 {$$ = $1;}
    ;


%%

int yywrap(){
    return 1;
}