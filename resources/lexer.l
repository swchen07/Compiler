%option noyywrap
%option nounput
%option noinput


%{

/* use a “SAVE_TOKEN” macro to keep the text of identifiers and numbers somewhere safe */
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
%}

/* 空白符和注释 */
WHTIESPACE              [ \t\n\r]*
LINECOMMET              "//".*
BLOCKCOMMET             "/*"[^*]*[*]+([^*/][^*]*[*]+)*"/"

/* 整数字面量 */
DECIMAL                 [1-9][0-9]*
OCTAL                   0[0-7]*
HEXADECIMAL             0[xX][0-9a-fA-F]+

/* 浮点数 */
REAL                    [0-9]+\.[0-9]+

/* 字符串 */
STRING                  \"(\\.|[^"\\])*\"


/* 标识符 */
IDENTIFIER              [a-zA-Z_][a-zA-Z0-9_]*


%%

    /* 空白符和注释 */
{WHTIESPACE}            {;}
{LINECOMMET}            {;}
{BLOCKCOMMET}           {;}

    /* 标识符 */
{IDENTIFIER}            {SAVE_TOKEN; return IDENTIFIER;}

    /* 运算符 */
    /* 关系运算符 */
"=="                    {return TOKEN(EQU);}
"!="                    {return TOKEN(NEQ);}
"<"                     {return TOKEN(LES);}
"<="                    {return TOKEN(LEQ);}
">"                     {return TOKEN(GRE);}
">="                    {return TOKEN(GEQ);}

    /* 算术运算符 */
"+"                     {return TOKEN(PLUS);}
"-"                     {return TOKEN(MINUS);}
"*"                     {return TOKEN(MUL);}
"/"                     {return TOKEN(DIV);}
"%"                     {return TOKEN(MOD);}

    /* 逻辑运算符 */
"&&"                    {return TOKEN(AND);}
"||"                    {return TOKEN(OR);}
"!"                     {return TOKEN(NOT);}

    /* 位运算符 */
"&"                     {return TOKEN(BAND);}
"|"                     {return TOKEN(BOR);}
"^"                     {return TOKEN(BXOR);}

    /*分隔符*/
"("                     {return TOKEN(LPAREN);}
")"                     {return TOKEN(RPAREN);}
"["                     {return TOKEN(LBRACKET);}
"]"                     {return TOKEN(RBRACKET);}
"{"                     {return TOKEN(LBRACE);}
"}"                     {return TOKEN(RBRACE);}
","                     {return TOKEN(COMMA);}
";"                     {return TOKEN(SEMI);}

    /* 赋值运算符 */
"="                     {return TOKEN(ASSIN);}

    /* 特殊符号 */
"."                     {return TOKEN(DOT);}
":"                     {return TOKEN(COLON);}
"?"                     {return TOKEN(QUES);}



    /* 关键字 */
    /* 数据类型 */
"int"                   {SAVE_TOKEN; return INT;}
"char"                  {SAVE_TOKEN; return CHAR;}
"bool"                  {SAVE_TOKEN; return BOOL;}
"void"                  {SAVE_TOKEN; return VOID;}
"string"                {SAVE_TOKEN; return STRING;}

    /* 挑战结构 */
"return"                {SAVE_TOKEN; return RETURN;}
"continue"              {SAVE_TOKEN; return CONTINUE;}
"break"                 {SAVE_TOKEN; return BREAK;}

    /* 分支结构 */
"if"                    {SAVE_TOKEN; return IF;}
"else"                  {SAVE_TOKEN; return ELSE;}

    /* 循环结构 */
"for"                   {SAVE_TOKEN; return FOR;}
"while"                 {SAVE_TOKEN; return WHILE;}


    /*  */
{DECIMAL}               {;}
{OCTAL}                 {;}
{HEXADECIMAL}           {;}

{REAL}                  {;}

{STRING}                {;}


%%