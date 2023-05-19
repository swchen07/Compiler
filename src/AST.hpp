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
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
public:

}

/**
 * @brief Decl基类
 * 
 */
class DeclAST : public BaseAST {
public:
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
}

/**
 * @brief Stmt基类和他的子类
 * 
 */
class StmtAST : public BaseAST {
public:
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
}

class ReturnAST : public StmtAST {
public: 
    ExpAST* retVal_;
    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

class BlockAST : public StmtAST {
public:

    /* the content */
}

class ForAST : public StmtAST {

}

class IfAST : public StmtAST {
public:
    
}

/**
 * @brief Exp基类和他的子类
 * 
 */
class ExpAST : public BaseAST {

}

class BinaryOpAST : public ExpAST {

}

class AssignAST : public ExpAST {

}

class IntAST : public ExpAST {

}

class CharAST : public ExpAST {

}

class IdentifierAST : public ExpAST {

}



