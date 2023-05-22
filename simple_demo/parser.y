

%{
#include <iostream>
#include <string>

int yylex();

void yyerror(const char *s) {
    std::printf("Error: %s", s);
}

using namespace std;

%}

%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
    std::string *strVal;
    int token;
    int intVal;
    BaseAST *astVal;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token ADD
%token LPAREN RPAREN LBRACE RBRACE
%token INT RETURN

%token <strVal> IDENTIFIER
%token <intVal> CONST_INT

// 非终结符的类型定义

%type <astVal> FuncDef FuncType Block Stmt Exp
%type <intVal> Number

/* 优先级和结合性定义 */

%%

CompUnit
    : FuncDef                                   {ast = $1;}
    ;

FuncDef
    : FuncType IDENTIFIER LPAREN RPAREN Block   {$$ = new FunctionAST($1, $2, $5);}
    ;

Block
    : LBRACE Stmt RBRACE                        {$$ = new BlockAST($2);}
    ;

FuncType
    : INT                                       {$$ = new string("int");}
    ;

Stmt
    : RETURN Exp ';'                            {$$ = new StmtAST($2);}
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
int main()
{
    yyparse();
}
