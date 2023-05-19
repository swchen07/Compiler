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

%token CONST
%token IDENTIFIER
%token CONST_INT CONST_CHAR CONST_FLOAT CONST_STR
// 非终结符的类型定义

%type CompUnit
%type FuncDef
%type <strVal> FuncType
%type FuncParaLists
%type FuncParam
%type Decl
%type ConstDecl
%type ConstDef
%type ConstList
%type ConstExp
%type ConstInitVal
%type VarDecl
%type Btype
%type VarList
%type VarDef

%type Block
%type BlockItem BlockItemNew
%type Stmt

%type PrimaryExp
%type Exp
%type ElseState
%type RetState

%type LVal
%type Number

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

/* CompUnit      ::= [CompUnit] (Decl | FuncDef); */
Program
    : CompUnit FuncDef
    | CompUnit Decl
    ;

CompUnit
    : CompUnit FuncDef                                   {}
    | CompUnit Decl
    | 
    ;

/* Decl          ::= ConstDecl | VarDecl; */
Decl
    : ConstDecl
    | VarDecl                                   {}
    ;

/* ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";"; */
ConstDecl
    : CONST Btype ConstDef ConstList SEMI
    ;

ConstList
    : ConstList COMMA ConstDef
    |
    ;

/* BType         ::= "int"; */
Btype
    : VOID
    | INT
    | CHAR
    ;

/* ConstDef      ::= IDENT "=" ConstInitVal; */
ConstDef
    : IDENTIFIER ASSIGN ConstInitVal
    ;

/* ConstInitVal  ::= ConstExp; */
ConstInitVal
    : ConstExp
    ;

/* VarDecl       ::= BType VarDef {"," VarDef} ";"; */
VarDecl
    : Btype VarDef VarList SEMI
    ;

VarList
    : VarList COMMA VarDef
    |
    ;

/* VarDef        ::= IDENT | IDENT "=" InitVal; */
VarDef
    : IDENTIFIER
    | IDENTIFIER ASSIGN InitVal
    ;

/* InitVal       ::= Exp; */
InitVal
    : Exp
    ;

/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block; */
FuncDef
    : FuncType IDENTIFIER LPAREN FuncParaLists RPAREN Block   {}
    ;

/* FuncType      ::= "void" | "int"; */
FuncType
    : INT                                       { $$ = new string("int"); }
    | VOID                                      { $$ = new string("void"); }
    | CHAR                                      { $$ = new string("char"); }
    ;

/* FuncFParams   ::= FuncFParam {"," FuncFParam}; */
FuncParaLists
    : FuncParams 
    | 
    ;

FuncParams
    : FuncParams COMMA FuncParam
    | FuncParam
    ;

/* FuncFParam    ::= BType IDENT; */
FuncParam
    : Btype IDENTIFIER
    ;

/* Block         ::= "{" {BlockItem} "}"; */
Block
    : LBRACE BlockItemNew RBRACE                {}
    ;

BlockItemNew
    : BlockItemNew BlockItem
    | 
    ;

/* BlockItem     ::= Decl | Stmt; */
BlockItem
    : Decl
    | Stmt
    ;

/* Stmt          ::= LVal "=" Exp ";"
                | [Exp] ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";"; */
Stmt
    : LVal ASSIGN Exp SEMI
    | Exp SEMI
    | SEMI
    | Block
    | IF LPAREN Exp RPAREN Stmt ElseState
    | WHILE LPAREN Exp RPAREN Stmt
    | BREAK SEMI
    | CONTINUE SEMI
    | RETURN RetState SEMI
    ;

LVal
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

PrimaryExp
    : LPAREN Exp RPAREN
    | LVal
    | Number
    ;

Number
    : CONST_INT
    | CONST_CHAR
    ;

Exp
    : PrimaryExp
    | ADD Exp 
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
