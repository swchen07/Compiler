/**
 * @file AST.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <llvm/IR/Value.h>
#include <iostream>
#include <vector>

/**
 * @brief 构造所有AST节点的基类，其中用指针管理对象
 * 
 */

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual llvm::Value* codeGen(CodeGenContext& context) =0;
};

class ASSIGNAST : public BaseAST {
public:
    string _var;
    int _val;
    ASSIGNAST(string var, int val): _var(var), _val(val) {};
    ~ASSIGNAST() = default;
    llvm::Value* codeGen(CodeGenerator& __Generator);
}




