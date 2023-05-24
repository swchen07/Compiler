![image-20230523010519034](image/image-20230523010519034.png)

> Ref
>
> <img src="image/image-20230523003708256.png" alt="image-20230523003708256" style="zoom:33%;" />
>
> **实验设计文档**
>
> https://www.chromium.org/developers/design-documents/
>
> https://www.industrialempathy.com/posts/design-docs-at-google
>
> 
>
> 模块名称:xxxx
>
> \1. 这个模块是什么?在整个系统中的地位如何?
>
> \2. 为什么要设计本模块?
>
> \3. 模块设计的具体方案和思想。
>
> \4. 本项目设计此模块的一些特性。
>
> \5. 如何使用本模块。
>
> \6. git 工作流。
>  \7. 其它你认为重要的东西。
>
> 
>
> Sysy: https://gitlab.eduxiji.net/nscscc/compiler2022



# 一、介绍

## 1.1 sysY介绍

本次实验完成了一个sysY语言的编译器，能够分析sysY语言的语法，并将其编译至LLVM IR，最后再编译至目标代码( .o 文件)。

sysY 是一种简单的编程语言，通常用于教学和学术研究目的。sysY 语言的设计旨在提供一个易于理解和实现的语言，用于介绍编译器设计和实现的基本概念。

我们实现的sysY编译器支持以下sysY语言特性:

1. 静态类型：sysY 是一种静态类型语言，所有变量在编译时必须声明其类型，并且类型检查是在编译阶段进行的。类型检查可以帮助捕捉许多常见的编程错误。
2. 基本数据类型：sysY 支持整数和浮点数类型。整数类型可以包括有符号和无符号的整数，可以指定不同的位宽。浮点数类型可以是单精度或双精度。
3. 数组：sysY 支持一维和多维数组。数组的长度可以在声明时指定或在运行时动态分配。可以使用索引访问和修改数组元素。
4. 表达式：sysY 支持基本的算术和逻辑表达式，包括算术运算符（如加法、减法、乘法、除法）、比较运算符（如等于、不等于、大于、小于）和逻辑运算符（如与、或、非）。
5. 控制流语句：sysY 支持条件语句和循环语句。条件语句包括 if-else 语句，根据条件的结果选择不同的执行路径。循环语句包括 for 循环和 while 循环，用于重复执行一段代码块。
6. 函数：sysY 支持函数的定义和调用。函数可以接受参数并返回值。函数定义包括函数名称、参数列表和函数体。函数调用可以将实际参数传递给函数，并接收返回值。
7. 输出语句：sysY 提供了输出语句，用于在程序执行过程中打印输出结果。可以打印字符串常量和变量的值。
8. 作用域：sysY 使用块作用域。变量在定义它们的代码块内可见，并且可以被内部的代码块重新定义。
9. 没有指针和复杂数据结构：sysY 简化了语言设计，不支持指针和复杂的数据结构（如结构体和类）。它专注于基本的数据类型和控制结构。



## 1.2 运行环境说明

- Flex & Bison：使用flex和bison生成词法分析器和语法分析器。
- LLVM-10：基于LLVM标准完成AST的构建、IR代码的生成；同时使用LLVM来完成编译器优化、目标代码生成。
- CMake：使用CMake来构建工程。

### 1.2.1 安装参考



### 1.2.2 工程搭建



### 1.2.3 使用说明



## 1.3 代码规范





## 1.4 分工说明







# 二、实验设计文档

## 2.1 词法分析设计

### 2.1.0 介绍

在实验报告的词法分析部分，我们将详细介绍sysY语言的词法规范和词法分析器的设计与实现过程。我们将描述sysY语言中各种词法单元的定义和识别规则，以及词法分析器的工作原理和算法。我们还将讨论词法错误处理和测试验证的方法，以确保词法分析器的正确性和鲁棒性。通过深入了解词法分析的重要性和功能，我们可以更好地理解编译器的工作原理和实现过程。



### 2.1.1 词法单元的定义和识别规则

1. 关键字（Keywords）：

   - 控制结构关键字：

     - `if`：用于条件语句，根据条件表达式的结果执行相应的代码块。

     - `else`：在条件语句中可选的分支，用于处理条件不满足的情况。

     - `while`：用于循环语句，当条件满足时重复执行代码块。

   - 数据类型关键字：

     - `int`：表示整数类型。

     - `float`：表示浮点数类型。

     - `char`：表示字符类型。

   - 修饰符关键字：

     - `const`：用于声明常量，表示该变量的值在程序执行期间不可修改。

     - `void`：表示无返回值或不接受参数的函数。

2. 标识符（Identifiers）： 标识符用来表示变量、函数、类等用户自定义的命名。

   - 标识符由字母、数字和下划线组成。
   - 标识符必须以字母或下划线开头，不能以数字开头。
   - 标识符区分大小写，因此大小写不同的标识符被视为不同的符号。

3. 常量（Literals）： 常量是固定的数值或字符值，包括整数、浮点数、字符、字符串等。

   - 整数常量：整数常量是不带小数点的数值，可以使用十进制、八进制或十六进制表示。例如：`42`、`0b1010`、`0o77`、`0xFF`。
   - 浮点数常量：浮点数常量是带有小数点的数值。可以使用十进制表示，也可以使用科学计数法表示。例如：`3.14`、`1.23e-5`。
   - 字符常量：字符常量是单个字符，用单引号括起来。例如：`'a'`、`'b'`、`'%'`。
   - 字符串常量：字符串常量是由多个字符组成的序列，用双引号括起来。例如：`"Hello, world!"`、`"sysY"`。

4. 运算符（Operators）： 运算符用于执行各种操作，如算术运算、逻辑运算、比较运算等。sysY语言中包括常见的运算符，如加法、减法、乘法、除法、赋值、逻辑与、逻辑或等。

   - 算术运算符：用于执行基本的算术操作，如加法、减法、乘法和除法。常见的算术运算符包括加号`+`、减号`-`、乘号`*`和除号`/`。
   - 赋值运算符：用于将一个值赋给变量。赋值运算符使用等号`=`表示，例如`a = 5`。
   - 逻辑运算符：用于执行逻辑操作，如逻辑与、逻辑或和逻辑非。逻辑与运算符表示为双与号`&&`，逻辑或运算符表示为双竖线`||`，逻辑非运算符表示为感叹号`!`。
   - 比较运算符：用于比较两个值之间的关系，如相等、不相等、大于、小于等。常见的比较运算符包括等于号`==`、不等于号`!=`、大于号`>`、小于号`<`、大于等于号`>=`和小于等于号`<=`。
   - 位运算符：用于对二进制位进行操作。常见的位运算符包括按位与`&`、按位或`|`、按位取反`~`、按位异或`^`、左移`<<`和右移`>>`。
   - 条件运算符：也称为三元运算符，用于根据条件选择不同的值。条件运算符使用问号`?`和冒号`:`组合，例如`condition ? value1 : value2`。
   - 其他运算符：sysY语言还支持其他一些运算符，如取地址运算符`&`、取值运算符`*`、下标运算符`[]`等。

   运算符在词法分析阶段会被识别为独立的词法单元，并传递给语法分析器进行解析。不同的运算符具有不同的优先级和结合性，编译器会按照运算符的规则进行解析和计算，确保表达式的正确性和准确性。



### 2.1.2 词法规范：正则表达式

在Lex中，正则表达式用于描述词法单元的模式。它们指定了需要匹配的字符序列的规则，并可以与特定的动作关联。以下是一些Lex约定用于描述正则表达式的常见语法：

| 格式  | 含义                           |
| ----- | ------------------------------ |
| a     | 字符a                          |
| "a"   | 即使a是一个元字符，它仍是字符a |
| \a    | 即使a是一个元字符，它仍是字符a |
| a*    | a的零次或多次重复              |
| a+    | a的一次或多次重复              |
| a?    | 一个可选的a                    |
| a\|b  | a或b                           |
| (a)   | a本身                          |
| [abc] | 字符a、b或c中的任一个          |
| [a-d] | 字符a、b、c或d中的任一个       |
| [^ab] | 除了a或b外的任一个字符         |
| .     | 除了新行之外的任一个字符       |
| {xxx} | 名字xxx表示的正则表达式        |



### 2.1.3 词法分析器设计

在词法分析器设计中，采用词法分析器生成工具（Flex）是一种常见的选择。Flex是一个词法分析器生成器，它可以根据给定的正则表达式规则和相应的动作生成用于词法分析的自动识别器。

Lex输入文件由三个部分组成：定义（defination）集，规则（rule）集以及辅助程序（auxiliary）集或用户程序（user routine）集。

```apl
{definations}
%%
{rules}
%%
{auxiliary routines}
```

#### 2.1.3.1 定义部分

##### Todo



#### 2.1.3.2 规则部分

##### Todo





## 2.2 语法分析设计

### 2.2.1 介绍

语法分析在编译器中扮演着关键的角色，它将源代码转化为抽象语法树表示，为后续的编译器阶段提供了基础。



### 2.2.2 语法规范

以下是sysY语言的正式语法规范，使用巴科斯范式（BNF）描述语法规则。

##### Todo： 要根据我们的语法规范修改，下面给出模版

```
<program> ::= <declaration_list>

<declaration_list> ::= <declaration> | <declaration_list> <declaration>

<declaration> ::= <type_specifier> <identifier> ";" | <type_specifier> <identifier> "(" ")" <compound_statement>

<type_specifier> ::= "int" | "void"

<identifier> ::= <letter> <identifier_tail>

<identifier_tail> ::= <letter_or_digit> <identifier_tail> | ε

<letter> ::= "A" | "B" | ... | "Z" | "a" | "b" | ... | "z"

<letter_or_digit> ::= <letter> | <digit>

<compound_statement> ::= "{" <local_declarations> <statement_list> "}"

<local_declarations> ::= <local_declaration> | <local_declarations> <local_declaration>

<local_declaration> ::= <type_specifier> <identifier> ";"

<statement_list> ::= <statement> | <statement_list> <statement>

<statement> ::= <expression_statement> | <compound_statement> | <selection_statement> | <iteration_statement> | <return_statement>

<expression_statement> ::= <expression> ";" | ";"

<selection_statement> ::= "if" "(" <expression> ")" <statement> | "if" "(" <expression> ")" <statement> "else" <statement>

<iteration_statement> ::= "while" "(" <expression> ")" <statement>

<return_statement> ::= "return" <expression> ";" | "return" ";"

<expression> ::= <var> "=" <expression> | <simple_expression>

<var> ::= <identifier>

<simple_expression> ::= <additive_expression> | <simple_expression> <relop> <additive_expression>

<additive_expression> ::= <term> | <additive_expression> <addop> <term>

<term> ::= <factor> | <term> <mulop> <factor>

<factor> ::= <var> | <call> | <num> | "(" <expression> ")"

<call> ::= <identifier> "(" ")" | <identifier> "(" <args> ")"

<args> ::= <expression> | <args> "," <expression>

<relop> ::= "<" | "<=" | ">" | ">=" | "==" | "!="

<addop> ::= "+" | "-"

<mulop> ::= "*" | "/"

<num> ::= <digit> | <digit> <num>

<digit> ::= "0" | "1" | ... | "9"
```

sysY语言的关键字包括：`int`, `void`, `if`, `else`, `while`, `return`。

sysY语言的运算符包括：`+`, `-`, `*`, `/`, `=`, `<`, `<=`, `>`, `>=`, `==`, `!=`。

sysY语言的语法结构包括：程序（`<program>`）、声明列表（`<declaration_list>`）、声明（`<declaration>`）、类型说明符（`<type_specifier>`）、标识符（`<identifier>`）、复合语句（`<compound_statement>`）、局部声明列表（`<local_declarations>`）、局部声明（`<local_declaration>`）、语句列表（`<statement_list>`）、语句（`<statement>`）、表达式语句（`<expression_statement>`）、选择语句（`<selection_statement>`）、循环语句（`<iteration_statement>`）、返回语句（`<return_statement>`）、表达式（`<expression>`）、变量（`<var>`）、简单表达式（`<simple_expression>`）、加法表达式（`<additive_expression>`）、项（`<term>`）、因子（`<factor>`）、函数调用（`<call>`）、实参列表（`<args>`）、关系运算符（`<relop>`）、加法运算符（`<addop>`）、乘法运算符（`<mulop>`）、数字（`<num>`）、数字字符（`<digit>`）。

这些语法规则和符号定义了sysY语言的语法结构和语法规则，编译器在语法分析阶段将根据这些规则进行源代码的解析和构建抽象语法树（AST）。



### 2.2.3 语法分析器设计方案

在设计sysY编译器的语法分析器时，采用了自底向上的语法分析方法，并选择了LALR(1)解析算法。为了实现语法分析器，使用了Yacc/Bison作为语法分析器生成工具。

自底向上的语法分析方法以输入的源代码作为起点，逐步构建语法规则的右部，并最终推导出起始符号，生成抽象语法树（AST）。相较于自顶向下方法，自底向上方法可以处理更复杂的文法，并具有更强的语法表达能力。

LALR(1)解析算法是一种常用的自底向上解析算法，它使用了向前看一个符号（Look-Ahead 1）来进行决策。LALR(1)算法通过构建LR(1)项目集族和状态转换表来解析输入的源代码。这种解析算法具有较高的效率和广泛的应用性。

为了生成语法分析器，选择了Yacc/Bison作为工具。Yacc/Bison是一对用于生成语法分析器的工具，它们根据提供的文法规范自动生成相应的语法分析器代码。通过定义文法规则和语义动作，Yacc/Bison可以生成解析输入的源代码，并构建抽象语法树。

在sysY编译器的设计中，通过编写sysY语言的文法规范并使用Yacc/Bison工具，生成了相应的语法分析器。该语法分析器利用LALR(1)解析算法来解析输入的源代码，并生成抽象语法树作为后续编译过程的基础。

采用自底向上的语法分析方法、LALR(1)解析算法以及Yacc/Bison工具，可以确保sysY编译器能够准确、高效地进行语法分析，并生成正确的抽象语法树。



#### 2.2.3.1 定义部分

##### Todo

#### 2.2.3.2 规则部分

##### Todo



### 2.2.4 抽象语法树（AST）

##### Todo： 要根据我们的AST修改，下面给出模版

AST的结构和表示方式可以根据具体的语言和编译器实现而有所不同，但通常包含以下类型的节点：

1. 标识符（Identifier）节点：用于表示变量、函数名等标识符的节点。
2. 常量（Literal）节点：用于表示常量值的节点，如整数、浮点数、字符串等。
3. 表达式（Expression）节点：用于表示各种表达式，如算术表达式、逻辑表达式、赋值表达式等。
4. 语句（Statement）节点：用于表示各种语句，如条件语句、循环语句、函数调用语句等。
5. 声明（Declaration）节点：用于表示变量声明、函数声明等语句。
6. 类型（Type）节点：用于表示变量或表达式的数据类型。
7. 控制流（Control Flow）节点：用于表示程序的控制流结构，如条件分支、循环等。

##### Todo 需要AST设计图，xml



#### 2.2.4.1 各个类的介绍



#### 2.2.4.5 示例代码及对应AST结构介绍

##### Todo： 要根据我们的AST修改，下面给出模版

下面是一个示例代码和其对应的简化的AST结构：

示例代码：

```
cssCopy code
int a = 10;
int b = 5;
int result = a + b;
```

对应的AST结构：

```
markdownCopy code
- Program
  - DeclarationStatement
    - TypeNode (int)
    - IdentifierNode (a)
    - LiteralNode (10)
  - DeclarationStatement
    - TypeNode (int)
    - IdentifierNode (b)
    - LiteralNode (5)
  - DeclarationStatement
    - TypeNode (int)
    - IdentifierNode (result)
    - BinaryExpressionNode (+)
      - IdentifierNode (a)
      - IdentifierNode (b)
```

在这个简化的AST中，根节点是Program节点，表示整个程序。每个DeclarationStatement节点表示一个变量的声明语句，包含变量的类型、标识符和初始值（如果有）。BinaryExpressionNode节点表示两个标识符相加的表达式。

通过构建和遍历AST，编译器可以从源代码中提取出语法结构和语义信息，并进行后续的分析和转换操作。



### 2.2.5 语法分析器的测试和验证

##### Todo

> 1. 编写测试用例：编写一组全面而具有代表性的测试用例，覆盖语法分析器的不同语法规则和边界情况。测试用例应包括合法的输入代码和非法的输入代码，以验证语法分析器的正确性和错误处理能力。
> 2. 语法规范验证：将测试用例与sysY语言的正式语法规范进行比对，确保语法分析器按照规范正确解析输入代码。检查是否有任何未处理的语法结构或语法错误。
> 3. 边界情况测试：测试处理语法规范中定义的边界情况，例如最大允许的标识符长度、嵌套层数等。验证语法分析器在处理这些特殊情况时是否能够正确识别和处理。
> 4. 错误处理测试：编写包含语法错误的测试用例，例如缺少分号、括号不匹配等。验证语法分析器能够准确地检测和报告这些错误，并给出恰当的错误信息。
> 5. 性能测试：对语法分析器进行性能测试，包括处理大型源代码文件或具有复杂语法结构的代码。评估语法分析器在处理大规模代码时的效率和内存消耗情况。
> 6. 与参考实现对比：如果有其他编译器或解析器实现sysY语言的参考实现，可以将测试用例同时运行在语法分析器和参考实现上，并对比其结果。这可以帮助发现潜在的问题或差异，并确保语法分析器的正确性。
> 7. 随机测试：使用随机生成的代码片段作为输入，测试语法分析器的鲁棒性和稳定性。这可以帮助发现不常见的错误情况和边界条件。
> 8. 自动化测试：建立自动化测试框架，包括编写自动化测试脚本和断言，以便能够快速运行和验证语法分析器的正确性。自动化测试可以提高测试的覆盖率和效率。



### 2.2.6 语法错误处理

##### Todo



### 2.2.7 AST可视化

##### Todo



## 2.3 语义分析设计

### 2.3.1 介绍

语义分析的主要目标是对源代码进行静态检查，发现和修复语义错误，并为后续阶段生成中间表示或目标代码提供准确的语义信息。

我们使用了LLVM的接口，手动将AST转化符合LLVM标准的IR代码



### 2.3.2 语义规则

##### Todo：以下四个模块加详细介绍或者代码

#### 2.3.2.1 类型检查

sysY语言是一种静态类型语言，因此在编译时会进行类型检查以确保操作的正确性。语义分析器将检查每个表达式和语句中的操作数和运算符之间的类型兼容性。例如，对于算术运算符，要求操作数必须具有相同的类型或可以进行隐式类型转换。如果发现类型不匹配或不兼容的情况，语义分析器将生成相应的类型错误。



#### 2.3.2.2 符号表和作用域规则

sysY语言使用块作用域规则，即在特定的代码块内声明的变量只在该块及其子块中可见。语义分析器将检查变量的作用域是否正确，并防止在非法的位置引用变量。例如，对于变量的引用，语义分析器会检查变量是否在当前作用域内可见。



#### 2.3.2.3  变量声明和使用规则

sysY语言要求在使用变量之前先进行声明。语义分析器将检查变量是否在使用之前已被声明，并且在同一作用域内不允许重复声明相同名称的变量。此外，语义分析器还会验证变量的类型和作用域等信息。



#### 2.3.2.4 函数调用和参数匹配

在sysY语言中，函数调用要求参数的数量和类型与函数声明中的参数列表匹配。语义分析器将检查函数调用的参数数量和类型是否正确，并匹配对应的函数声明。如果存在参数不匹配的情况，语义分析器将生成相应的错误消息。



### 2.3.3 语义类型

#### 2.3.3.1 Declare类





#### 2.3.3.2 Stmt抽象类





#### 2.3.3.3  VarType抽象类





#### 2.3.3.4 Expr抽象类







### 2.3.4 语义错误处理

##### Todo

> 说明语义分析器如何检测和报告语义错误，包括类型错误、未声明的变量、重复声明等。解释语义错误的分类和处理策略，如报错、警告或修复。



## 2.4 运行环境设计

#### Todo

### 2.4.1 创建IR上下文环境



### 2.4.2 创建IR模块



### 2.4.3 符号表



### 2.4.4 记录当前函数



### 2.4.5 break & continue 目的地址栈



### 2.4.6 结构体/共用体映射表



## 2.5 代码生成设计

首先实例化`llvm::sys::getDefaultTargetTriple`，该对象包含了目标机器的许多参数。然后我们调用`llvm::TargetMachine`的接口即可把LLVM中间代码编译成目标机器的汇编代码。具体请参考LLVM官方文档。

##### Todo 确认下面代码和我们使用的是否是同一份

```cpp
//Generate object code
void CodeGenerator::GenObjectCode(std::string FileName) {
	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();
	std::string Error;
	auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
	if (!Target) {
		throw std::runtime_error(Error);
		return;
	}
	auto CPU = "generic";
	auto Features = "";
	llvm::TargetOptions opt;
	auto RM = llvm::Optional<llvm::Reloc::Model>();
	auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
	Module->setDataLayout(TargetMachine->createDataLayout());
	Module->setTargetTriple(TargetTriple);
	std::error_code EC;
	llvm::raw_fd_ostream Dest(FileName, EC, llvm::sys::fs::OF_None);
	if (EC) {
		throw std::runtime_error("Could not open file: " + EC.message());
		return;
	}
	auto FileType = llvm::CGFT_ObjectFile;
	llvm::legacy::PassManager PM;
	if (TargetMachine->addPassesToEmitFile(PM, Dest, nullptr, FileType)) {
		throw std::runtime_error("TargetMachine can't emit a file of this type");
		return;
	}
	PM.run(*Module);
	Dest.flush();
}
```





## 2.6 符号表设计

##### Todo





## 2.7 进阶主题设计

##### Todo







# 三、运行结果

> 请附上你的源语言在你的编译器下的产生二进制或其他东西的过程，以及在第二节功能测试中的结果。

##### Todo





## 附：提交说明

**提交说明:**

本次提交主要使用学在浙大进行提交，同时为了避免这个系统出现常见的无法解释的问题(赶在DDL提交 是会出现各种事故的，助教不会视作不可抗力，请同学们自行斟酌)，助教也同时接受钉钉/邮箱提交(这 两个工具都有时间戳)。

提交DDL: 2023.5.28 22:00 一旦延后评分下降半个评级，然后每隔12小时再下降半个评级。例如:假 如你本可以评分为A+，但是你不小心在2023.5.28 22:01:00 才提交代码，于是你的评分可能降为A，如 果你把“十点”记成了2023.5.29 上午十点,却又不小心在2023.5.29 10:01:00才提交代码，那你的评分确 定从A+ -> A了。

提交的内容一定是一个压缩包，压缩包命名为**组名****_2023****编译原理大程**， 压缩包内有**包含组员的学号和 名字的文件**以及**实验报告**以及**源代码**。

提交时在学在浙大上一般由组长提交一份，但是为了避免组长出状况，组员也可以自己提交。