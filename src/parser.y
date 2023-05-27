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
	char charVal;
    BaseAST *astVal;
	CompUnits *compUnits;
	Stmts *stmts;
	Exprs *exprs;
    ArgAST *argVal;
    ArgListAST *argList;
    ExprListAST *exprList;
    ExprAST *expVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token EQU NEQ LES LEQ GRE GEQ
%token ADD SUB MUL DIV MOD
%token AND OR NOT
%token BAND BOR BXOR
%token LPAREN RPAREN LBRACE RBRACE  LBRACKET RBRACKET COMMA SEMI
%token ASSIGN DOT COLON QUES ELLIPSES

%token <strVal> INT CHAR SHORT VOID
%token RETURN CONTINUE BREAK STATIC
%token IF ELSE
%token FOR WHILE

%token CONST
%token <strVal> IDENTIFIER
%token <intVal> CONST_INT 
%token <charVal> CONST_CHAR 
%token <strVal> CONST_STR
%token CONST_FLOAT
// 非终结符的类型定义

%type <astVal> Program
%type <compUnits> CompUnit
%type <astVal> FuncDef
%type <strVal> FuncType

%type <argList> ArgList
%type <argList> _ArgList
%type <argVal> Arg

%type <exprList> ExpList
%type <exprList> _ExpList

%type <astVal> Decl
%type ConstDecl
%type ConstDef
%type ConstList
%type <astVal> ConstExp
%type ConstInitVal
%type <astVal> VarDecl
%type <strVal> Btype
%type VarList
%type <astVal> VarDef


%type <exprs> ArrDef ArrVal
%type <astVal> InitVal

%type <astVal> Block
%type <astVal> BlockItem 
%type <stmts> BlockItemNew
%type <astVal> Stmt SmooStmt

%type <astVal> PrimaryExp
%type <astVal> Exp
%type <astVal> ElseState
%type <astVal> RetState

%type <astVal> LVal
%type <intVal> Number
%type <astVal> Constant

%type <astVal> ArrValF

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
	| CompUnit STATIC Decl                                     { $$ = (CompUnits*)$1; $$->push_back((CompUnitAST*)$3); }
    | 													{ $$ = new CompUnits(); }
    ;
/*    | CompUnit Decl                                     { $$ = (CompUnits*)$1; $$->push_back((CompUnitAST*)$2); }*/

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
    : Btype VarDef VarList SEMI                     { $$ = new VarDeclAST(*$1, (VarDefAST*)$2);}
	| Btype IDENTIFIER ArrDef SEMI					{ $$ = new ArrDefAST(*$1, *$2, (Exprs*)$3); }
    ;

VarList
    : VarList COMMA VarDef
    |                                               { ; }
    ;

/* VarDef        ::= IDENT | IDENT "=" InitVal; */
VarDef
    : IDENTIFIER                                    { $$ = new VarDefAST(*$1);}
    | IDENTIFIER ASSIGN InitVal                     { $$ = new VarDefAST(*$1, (ExprAST*)$3);}
    ;

ArrDef
	: ArrDef LBRACKET ConstExp RBRACKET 			{ $$ = (Exprs*)$1; $$->push_back((ExprAST*)$3); }
	| 												{ $$ = new Exprs(); }
	;

/* InitVal       ::= Exp; */
InitVal
    : Exp                                           { $$ = $1; }
    ;

/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block; */
/*FuncDef
    : FuncType IDENTIFIER LPAREN RPAREN Block   { $$ = new FuncDefAST(*$1, *$2, (BlockAST*)$5);}
    ;*/

FuncDef
    : FuncType IDENTIFIER LPAREN ArgList RPAREN SEMI    { $$ = new FuncDefAST(*$1, *$2, (ArgListAST*)$4); }
    | FuncType IDENTIFIER LPAREN ArgList RPAREN Block   { $$ = new FuncDefAST(*$1, *$2, (ArgListAST*)$4, (BlockAST*)$6); }
    ;


/* FuncType      ::= "void" | "int"; */
FuncType
    : INT                                       { $$ = $1; }
    | VOID                                      { $$ = $1; }
    | CHAR                                      { $$ = $1; }
    ;


ArgList:	_ArgList COMMA Arg										{  $$ = $1; $$->push_back($3);   }
			| _ArgList COMMA ELLIPSES								{  $$ = $1; $$->SetVarArg();   }
			| Arg													{  $$ = new ArgListAST(); $$->push_back($1);   }
			| ELLIPSES												{  $$ = new ArgListAST(); $$->SetVarArg();   }
			|														{  $$ = new ArgListAST(); }
			;

_ArgList:	_ArgList COMMA Arg										{  $$ = $1; $$->push_back($3);   }	 
			| Arg													{  $$ = new ArgListAST(); $$->push_back($1);   }
			;

/* VarType
    : Btype                                             { $$ = $1; }
    | BType PTR                                         { $$ = new PointerType(*$1); }
    ;

Arg:		VarType IDENTIFIER										{  $$ = new ArgAST(*$1, *$2);   }
			| VarType												{  $$ = new ArgAST(*$1);   }
			;
*/

Arg:		Btype IDENTIFIER										{  $$ = new ArgAST(*$1, *$2);   }
			| Btype												    {  $$ = new ArgAST(*$1);   }
			;

/* Block         ::= "{" {BlockItem} "}"; */
Block
    : LBRACE BlockItemNew RBRACE                { $$ = new BlockAST((Stmts*)$2);}
    ;

BlockItemNew
    : BlockItemNew BlockItem					{ $$ = (Stmts*)$1; if ($2 != NULL)$$->push_back((CompUnitAST*)$2); }
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

SmooStmt
    : LVal ASSIGN Exp						{ $$ = new AssignAST((LeftValAST*)$1, (ExprAST*)$3); }
    | Exp								    { $$ = $1; }
	| ArrValF ASSIGN Exp					{ $$ = new AssignArrAST((ArrValAST*)$1, (ExprAST*)$3); }
    | 									    { $$ = NULL; }
    | BREAK                                 { $$ = new BreakStmtAST(); }
    | CONTINUE                              { $$ = new ContinueStmtAST(); }
    | RETURN RetState					    { $$ = new ReturnStmtAST((ExprAST*)$2);}

Stmt
    : SmooStmt SEMI						        { $$ = $1; }
    | Block										{ $$ = $1; }
    | FOR LPAREN SmooStmt SEMI Exp SEMI SmooStmt RPAREN Block   { $$ = new ForStmtAST((StmtAST*)$3, (ExprAST*)$5, (StmtAST*)$7, (BlockAST*)$9); }
    | IF LPAREN Exp RPAREN Block ElseState      { $$ = new IfElseStmtAST((ExprAST*)$3, (BlockAST*)$5, (BlockAST*)$6); }
    | WHILE LPAREN Exp RPAREN Block             { $$ = new WhileStmtAST((ExprAST*)$3, (BlockAST*)$5); }
    ;

LVal
    : IDENTIFIER								{ $$ = new LeftValAST(*$1); }
    ;

ArrValF
	: IDENTIFIER ArrVal							{ $$ = new ArrValAST(*$1, (Exprs*)$2); }

ArrVal
	: ArrVal LBRACKET Exp RBRACKET		{ $$ = (Exprs*)$1; $$->push_back((ExprAST*)$3); }
	|									{ $$ = new Exprs(); }
	;

ElseState
    : ELSE Block                        {$$ = $2; }
    |                                   {$$ = NULL; }
    ;

RetState
    : Exp								{$$ = $1;}
    |                                   {$$ = NULL; }
    ;

PrimaryExp
    : LPAREN Exp RPAREN					{ $$ = $2; }
    | LVal								{ $$ = $1; }
    | Constant							{ $$ = $1; }	
    ;

Constant
    : CONST_INT							{ $$ = new Constant($1); }
    | CONST_CHAR						{ $$ = new Constant($1); }
    | CONST_STR                         { $$ = new StringType(*$1); }
    ;

Exp
    : PrimaryExp						{ $$ = $1; }	
	| ArrValF							{ $$ = (ArrValAST*)$1; }					
    | ADD Exp %prec NOT					{ $$ = new MoncPlus((ExprAST*)$2); }
    | SUB Exp %prec NOT					{ $$ = new MoncMinus((ExprAST*)$2); }
    | NOT Exp							{ $$ = new LogicNot((ExprAST*)$2); }
    | BAND LVal	%prec NOT			    { $$ = new AddressOf((LeftValAST*)$2); }

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

    | IDENTIFIER LPAREN ExpList RPAREN	 {  $$ = new FuncCallAST(*$1, $3);   }
	;

ExpList:	_ExpList COMMA Exp									{  $$ = $1; $$->push_back((ExprAST*)$3);   }
			| Exp                           					{  $$ = new ExprListAST(); $$->push_back((ExprAST*)$1);   }
			|													{  $$ = new ExprListAST();   }
			;

_ExpList:	_ExpList COMMA Exp 									{  $$ = $1; $$->push_back((ExprAST*)$3);   }
			| Exp                       						{  $$ = new ExprListAST(); $$->push_back((ExprAST*)$1);   }
			;

ConstExp
	: CONST_INT							{ $$ = new Constant($1); }
	;
%%
