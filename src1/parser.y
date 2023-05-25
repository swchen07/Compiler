%{
#include "AST.hpp"
#include <iostream>
#include <string>

int yylex(void);
extern BaseAST* Root; 

void yyerror(char *s)
{
	extern int yylineno;	// defined and maintained in lex
	extern char *yytext;	// defined and maintained in lex
	int len=strlen(yytext);
	int i;
	char buf[512]={0};
	for (i=0;i<len;++i)
	{
		sprintf(buf,"%s%d ",buf,yytext[i]);
	}
	fprintf(stderr, "ERROR: %s at symbol '%s' on line %d\n", s, buf, yylineno);
}


using namespace std;

%}

%output "parser.cpp"

%union {
    std::string* strVal;
	float floatVal;
    int intVal;
    BaseAST *astVal;
	CompUnits *compUnits;
	Stmts *stmts;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token EQU NEQ LES LEQ GRE GEQ
%token ADD SUB MUL DIV MOD
%token AND OR NOT
%token BAND BOR BXOR
%token LPAREN RPAREN LBRACE RBRACE COMMA SEMI
%token ASSIGN DOT COLON QUES

%token <strVal> INT CHAR SHORT VOID
%token RETURN CONTINUE BREAK
%token IF ELSE
%token FOR WHILE

%token CONST
%token <strVal> IDENTIFIER
%token <intVal> CONST_INT 
%token CONST_CHAR CONST_FLOAT CONST_STR
// 非终结符的类型定义

%type <astVal> Program
%type <compUnits> CompUnit
%type <astVal> FuncDef
%type <strVal> FuncType
%type FuncParaLists
%type FuncParam
%type <astVal> Decl
%type ConstDecl
%type ConstDef
%type ConstList
%type ConstExp
%type ConstInitVal
%type <astVal> VarDecl
%type <strVal> Btype
%type VarList
%type <strVal> VarDef

%type <astVal> Block
%type <astVal> BlockItem 
%type <stmts> BlockItemNew
%type <astVal> Stmt

%type <astVal> PrimaryExp
%type <astVal> Exp
%type ElseState
%type <astVal> RetState

%type <astVal> LVal
%type <intVal> Number
%type <astVal> Constant

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

%start Program

%%

/* CompUnit      ::= [CompUnit] (Decl | FuncDef); */
/* 	: FuncDef 											{auto c = new CompUnits(); c->push_back((CompUnitAST*)$1); $$ = new ProgramAST(c); Root = $$;} */
/*	| CompUnit											{$$ = new ProgramAST($1); Root = $$;} */
Program							
	: CompUnit 											{ $$ = new ProgramAST((CompUnits*)$1); Root = $$;}
	;

CompUnit
    : CompUnit FuncDef									{ $$ = (CompUnits*)$1; $$->push_back((CompUnitAST*)$2); }
    | 													{ $$ = new CompUnits(); }
    ;

/* Decl          ::= ConstDecl | VarDecl; */
Decl
    : ConstDecl
    | VarDecl                                           { $$ = $1; }
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
    : VOID                          { $$ = $1; }
    | INT                           { $$ = $1; }
    | SHORT                         { $$ = $1; }
    | CHAR                          { $$ = $1; }
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
    : Btype VarDef VarList SEMI                     { $$ = new VarDeclAST(*$1, *$2);}
    ;

VarList
    : VarList COMMA VarDef
    |                                               { ; }
    ;

/* VarDef        ::= IDENT | IDENT "=" InitVal; */
VarDef
    : IDENTIFIER                                    { $$ = $1;}
    | IDENTIFIER ASSIGN InitVal
    ;

/* InitVal       ::= Exp; */
InitVal
    : Exp
    ;

/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block; */
FuncDef
    : FuncType IDENTIFIER LPAREN RPAREN Block   { $$ = new FuncDefAST(*$1, *$2, (BlockAST*)$5);}
    ;

/* FuncType      ::= "void" | "int"; */
FuncType
    : INT                                       { $$ = $1; }
    | VOID                                      { $$ = $1; }
    | CHAR                                      { $$ = $1; }
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
    : LBRACE BlockItemNew RBRACE                { $$ = new BlockAST((Stmts*)$2);}
    ;

BlockItemNew
    : BlockItemNew BlockItem					{ $$ = (Stmts*)$1; if ($2 != NULL)$$->push_back((StmtAST*)$2); }
    | 											{ $$ = new Stmts(); }
    ;

/* BlockItem     ::= Decl | Stmt; */
BlockItem
    : Decl                                      { $$ = $1;}
    | Stmt										{ $$ = $1;}
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
    : LVal ASSIGN Exp SEMI						{ std::cout << "assign" << std::endl; $$ = new AssignAST((LeftValAST*)$1, (ExprAST*)$3); }
    | Exp SEMI									{ $$ = $1; }
    | SEMI										{ $$ = NULL; }
    | Block										{ $$ = $1; }
    | FOR 
    | IF LPAREN Exp RPAREN Stmt ElseState
    | WHILE LPAREN Exp RPAREN Stmt
    | BREAK SEMI
    | CONTINUE SEMI
    | RETURN RetState SEMI				{$$ = new ReturnStmtAST((ExprAST*)$2);}
    ;

LVal
    : IDENTIFIER						{ $$ = new LeftValAST(*$1); }
    ;

ElseState
    : ELSE Stmt
    |
    ;

RetState
    : Exp								{$$ = $1;}
    |
    ;

PrimaryExp
    : LPAREN Exp RPAREN
    | LVal								{ $$ = $1; }
    | Constant							{ $$ = $1; }				
    ;

Constant
    : CONST_INT							{ $$ =  new Constant($1); }
    | CONST_CHAR
    ;

Exp
    : PrimaryExp						{ $$ = $1; }						
    | ADD Exp %prec NOT					{ $$ = new MoncPlus((ExprAST*)$2); }
    | SUB Exp %prec NOT					{ $$ = new MoncMinus((ExprAST*)$2); }
    | NOT Exp							{ $$ = new LogicNot((ExprAST*)$2); }

    | Exp ADD Exp						{$$ = new Addition((ExprAST*)$1, (ExprAST*)$3);}
    | Exp SUB Exp						{$$ = new Subtraction((ExprAST*)$1, (ExprAST*)$3);}
    | Exp MUL Exp						{$$ = new Multiplication((ExprAST*)$1, (ExprAST*)$3);}
    | Exp DIV Exp						{$$ = new Division((ExprAST*)$1, (ExprAST*)$3);}
    | Exp MOD Exp						{$$ = new Modulation((ExprAST*)$1, (ExprAST*)$3);}

    | Exp EQU Exp						{$$ = new Equal((ExprAST*)$1, (ExprAST*)$3);}
    | Exp NEQ Exp						{$$ = new NotEqual((ExprAST*)$1, (ExprAST*)$3);}
    | Exp LES Exp						{$$ = new LessThan((ExprAST*)$1, (ExprAST*)$3);}
    | Exp LEQ Exp						{$$ = new LessEqu((ExprAST*)$1, (ExprAST*)$3);}
    | Exp GRE Exp						{$$ = new GreThan((ExprAST*)$1, (ExprAST*)$3);}
    | Exp GEQ Exp						{$$ = new GreEqu((ExprAST*)$1, (ExprAST*)$3);}

    | Exp AND Exp						{$$ = new AndOp((ExprAST*)$1, (ExprAST*)$3);}
    | Exp OR  Exp						{$$ = new OrOp((ExprAST*)$1, (ExprAST*)$3);}

    | Exp BAND Exp
    | Exp BOR  Exp
    | Exp BXOR Exp
	;

ConstExp
	:
	;
%%
