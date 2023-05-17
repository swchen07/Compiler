%{
#include "AST.hpp"

int yylex();

void yyerror(const char *s) {
    std::printf("Error: %s", s);
}

using namespace std;

%}

%union {
    std::string *string;
    int token;
    int intVal;
    float floatVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token EQU NEQ LES LEQ GRE GEQ
%token PLUS MINUS MUL DIV MOD
%token AND OR NOT
%token BAND BOR BXOR
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA SEMI
%token ASSIGN DOT COLON QUES

%token INT CHAR BOOL VOID STRING
%token RETURN CONTINUE BREAK
%token IF ELSE
%token FOR WHILE

// 非终结符的类型定义


%%



%%
