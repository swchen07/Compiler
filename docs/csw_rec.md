A record file for Chen Shaowen. 

## 课程内容回顾

编译器实现了什么：

把文本形式的源代码变成二进制形式的可执行文件：
1. 编译：将源代码编译为汇编代码
2. 汇编：将汇编代码汇编为目标文件
3. 链接：将目标文件链接为可执行文件

本次课程项目内容：设计一个程序, 将输入的 SysY 源代码, 编译到 RISC-V 汇编：
1. 前端：通过词法分析和语法分析, 将源代码解析成抽象语法树 (AST). 通过语义分析, 扫描抽象语法树, 检查其是否存在语义错误.
    1. 词法分析器（lexer）的作用：把字节流转换成为单词流（token），忽略一些无意义内容
    2. 语法分析器（parser）的作用：按照程序的语法规则, 将输入的 token 流变成程序的 AST.Parser 会通过某些语法分析算法, 例如 LL 分析法或 LR 分析法, 对 token 流做一系列的分析, 并最终得到 AST.(token 和 AST 这类数据结构仅在编译器内部出现, 并没有固定的规范. 它们的设计可以有很多种形式, 只要能够方便程序处理即可.)
    3. 语义分析：在语法分析的基础上, 编译器会对 AST 做进一步分析, 以期 “理解” 输入程序的语义, 为之后的 IR 生成做准备. 一个符合语法定义的程序未必符合语义定义。
        - 建立符号表, 跟踪程序里变量的声明和使用, 确定程序在某处用到了哪一个变量, 同时也可发现变量重复定义/引用未定义变量之类的错误.
        - 进行类型检查, 确定程序中是否存在诸如 “对整数变量进行数组访问” 这种类型问题. 同时标注程序中表达式的类型, 以便进行后续的生成工作. 对于某些编程语言 (例如 C++11 之后的 C++, Rust 等等), 编译器还会进行类型推断.
        - 进行必要的编译期计算. SysY 中支持使用常量表达式作为数组定义时的长度, 而我们在生成 IR 之前, 必须知道数组的长度(SysY 不支持 VLA), 这就要求编译器必须能在编译的时候算出常量表达式的值, 同时对那些无法计算的常量表达式报错. 对于某些支持元编程的语言, 这一步可能会非常复杂.


2. 中端: 将抽象语法树转换为中间表示 (IR), 并在此基础上完成一些机器无关优化.
    这里选择LLVM了，首先要能写完这个实验吧至少

3. 后端: 将中间表示转换为目标平台的汇编代码, 并在此基础上完成一些机器相关优化.
    1. **指令选择**: 决定 IR 中的指令应该被翻译为哪些目标指令系统的指令. 例如前文的 Koopa IR 程序中出现的 lt 指令可以被翻译为 RISC-V 中的 slt/slti 指令.
    2. *寄存器分配: 决定 IR 中的值和指令系统中寄存器的对应关系. 例如前文的 Koopa IR 程序中的 @x, %cond, %0 等等, 它们最终可能会被放在 RISC-V 的某些寄存器中. 由于指令系统中寄存器的数量通常是有限的 (RISC-V 中只有 32 个整数通用寄存器, 且它们并不都能用来存放数据), 某些值还可能会被分配在内存中.
    3. *指令调度: 决定 IR 生成的指令序列最终的顺序如何. 我们通常希望编译器能生成一个最优化的指令序列, 它可以最大程度地利用目标平台的微结构特性, 这样生成的程序的性能就会很高. 例如编译器可能会穿插调度访存指令和其他指令, 以求减少访存导致的停顿.

## Part1 词法、语法分析

需要了解：
1. EBNF
这种使用大写蛇形命名法的符号, 或者被双引号引起的字符串, 被称为终结符, 它们不能进一步被其他符号所替换, 你也不会在 EBNF 中看到它们出现在规则的左侧. 我们的目标是, 利用 EBNF 中的规则, 把开始符号推导成一系列终结符.

简化词法分析器和语法分析器，需要先选定编译语言，设计CFG。

### parser开发日志

1. 首先需要手写语法
```
参考sysY语言的文法，由于文法是EBNF，所以首先需要对[]和{}进行处理：
`term -> term { op term }` becomes:
    term -> term new_symbol
    new-symbol -> e | new_symbol op term

`if_stm -> if exp statement [else_statement]` becomes:
    if_stm -> if exp statement new_symbol
    new-symbol -> e | else_statement


同时由于结合性和优先级可以通过yacc声明实现，所以可以对文法进行简化

CompUnit      ::= [CompUnit] (Decl | FuncDef);

Decl          ::= ConstDecl | VarDecl;
ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
BType         ::= "int";
ConstDef      ::= IDENT "=" ConstInitVal;
ConstInitVal  ::= ConstExp;
VarDecl       ::= BType VarDef {"," VarDef} ";";
VarDef        ::= IDENT | IDENT "=" InitVal;
InitVal       ::= Exp;

FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncType      ::= "void" | "int";
FuncFParams   ::= FuncFParam {"," FuncFParam};
FuncFParam    ::= BType IDENT;

Block         ::= "{" {BlockItem} "}";
BlockItem     ::= Decl | Stmt;
Stmt          ::= LVal "=" Exp ";"
                | [Exp] ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";";

Exp           ::= LOrExp;
LVal          ::= IDENT;
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
Number        ::= INT_CONST;
UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
UnaryOp       ::= "+" | "-" | "!";
FuncRParams   ::= Exp {"," Exp};
MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp       ::= EqExp | LAndExp "&&" EqExp;
LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
ConstExp      ::= Exp;


```
2. 抽象语法树
    - BaseAST
        - CompUnitAST
        - DeclAST
            - VarDeclAST
            - FuncDefAST
        - ExpAST
            - AssignAST
            - BinaryOpAST
            - IntAST
            - CharAST
            - IdentifierAST

        - StmtAST
            - ReturnAST
            
            - 



