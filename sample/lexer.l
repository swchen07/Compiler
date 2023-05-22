%option noyywrap
%option nounput
%option noinput

%{


#include <cstdlib>
#include <string>

#include "parser.hpp"


%}

/* 整数字面量 */
DECIMAL                 [1-9][0-9]*

/* 标识符 */
IDENTIFIER              [a-zA-Z_][a-zA-Z0-9_]*

EQUAL                   =

%%

EQUAL                   {return ASSIGN;}

    /* 暂时参考北大在线文档给的demo */
    /* 标识符 */
    /* yylval 用来向 parser 传递 lexer 读取到的内容 */
    /* 遇到整数字面量, 先把读取到的字符串转换成整数, 然后存起来, 并返回对应的 token. */
{IDENTIFIER}            {yylval.string = std::string(yytext, yyleng); return IDENTIFIER;}

    /*  */
{DECIMAL}               {yylval.intVal = strtol(yytext, nullptr, 0); return INT;}

.                       { printf("Unknown token!/n");}

%%