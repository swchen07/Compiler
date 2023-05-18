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
    std::string *strVal;
    int token;
    int intVal;
    float floatVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token EQU NEQ LES LEQ GRE GEQ
%token ADD SUB MUL DIV MOD
%token AND OR NOT
%token BAND BOR BXOR
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA SEMI
%token ASSIGN DOT COLON QUES

%token INT CHAR BOOL VOID STRING
%token RETURN CONTINUE BREAK
%token IF ELSE
%token FOR WHILE

%token IDENTIFIER

// 非终结符的类型定义

%type CompUnit
%type FuncDef
%type <strVal> FuncType
%type FuncParaLists
%type FuncParam
%type Decl
%type VarDecl
%type VarType
%type VarList
%type VarDef

%type Block
%type BlockItem BlockItemNew
%type Stmt

%type Exp
%type ElseState
%type RetState

%type LeftVal


/* 优先级和结合性定义 */
%right	ASSIGN
%left	OR
%left	AND
%left	BOR
%left	BXOR
%left	BAND
%left	EQU NEQ
%left	GEQ GRE LES LEQ
%left	ADD SUB
%left	MUL DIV MOD

%%

CompUnit
    : FuncDef                                   {}
    ;

FuncDef
    : FuncType IDENTIFIER LPAREN FuncParaLists RPAREN Block   {}
    ;

FuncType
    : INT                                       { $$ = new string("int"); }
    | VOID                                      { $$ = new string("void"); }
    | CHAR                                      { $$ = new string("char"); }
    ;

FuncParaLists
    : FuncParams 
    | 
    ;

FuncParams
    : FuncParams COMMA FuncParam
    | FuncParam
    ;

FuncParam
    : VarType IDENTIFIER

Decl
    : VarDecl                                   {}
    ;

VarDecl
    : VarType VarDef VarList SEMI
    ;

VarType
    : VOID
    | INT
    | CHAR
    ;

VarList
    : VarList COMMA VarDef
    |
    ;

VarDef
    : IDENTIFIER
    | IDENTIFIER ASSIGN Exp
    ;

Block
    : LBRACE BlockItemNew RBRACE                {}
    ;

BlockItemNew
    : BlockItemNew BlockItem
    | 
    ;

BlockItem
    : Decl
    | Stmt
    ;

Stmt
    : LeftVal ASSIGN Exp SEMI
    | Exp SEMI
    | SEMI
    | IF LPAREN Exp RPAREN Stmt ElseState
    | WHILE LPAREN Exp RPAREN Stmt
    | BREAK SEMI
    | CONTINUE SEMI
    | RETURN RetState SEMI
    ;

LeftVal
    : IDENTIFIER
    ;

ElseState
    : ELSE Stmt
    |
    ;

RetState
    : Exp
    |
    ;

Exp
    : ADD Exp 
    | SUB Exp
    | NOT Exp
    
    | Exp ADD Exp
    | Exp SUB Exp
    | Exp MUL Exp
    | Exp DIV Exp
    | Exp MOD Exp

    | Exp EQU Exp
    | Exp NEQ Exp
    | Exp LES Exp
    | Exp LEQ Exp
    | Exp GRE Exp
    | Exp GEQ Exp

    | Exp AND Exp
    | Exp OR  Exp

    | Exp BAND Exp
    | Exp BOR  Exp
    | Exp BXOR Exp
    ;

%%
