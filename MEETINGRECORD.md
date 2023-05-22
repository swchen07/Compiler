# Meeting Record for Development

## 2023.5.16

### 实现思路
完全使用LLVM框架

### 开发方式
1. 开发环境：WSL上的ubuntu子系统
2. 使用VScode连接WSL进行开发
3. 使用Github进行项目管理
4. 使用C++进行编译器开发
5. 

### 参考文献

互联网项目参考：https://gnuu.org/2009/09/18/writing-your-own-toy-compiler/

助教提供：https://toscode.gitee.com/DaviesGit/SysY_compiler/

助教提供：https://pku-minic.github.io/online-doc/#/

### 待办事项

1. 学习LLVM框架的使用，阅读学习参考文献。
2. 讨论汇总代码风格，要求参考验收细则：
   代码风格的考察重点在于可读性。可读性是指其他人是否能够通过代码快速理解编码者的意图。有意义的命名、合理的模块设计、适当的注释、较强的一致性等可以增强可读性。一致性是指编码时采用的格式细节是否始终保持不变，强一致性会降低阅读的难度，增加可读性。建议自行搜索你所使用的语言的编码规范作为参考。
   代码规范参考：
   https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/
3. 语法定义：实现C语言的子集。
