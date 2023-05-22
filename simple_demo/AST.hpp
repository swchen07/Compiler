/**
 * @file AST.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <llvm/IR/Value.h>
#include <string>
#include "IRGenerator.hpp"

/**
 * @brief type类型的id
 * 
 */

enum TypeID{
    Int, 
    Char
};

class VarType {
public:
    VarType(int) {type=Int;}
    VarType(char) {type=Char;}
    VarType(string name) {
        if (name == 'int') type = Int; 
        else if (name == 'char') type = Char; 
    } 
    ~VarType(){}
    GetType() {return type;}
private: 
    TypeID type;
}


/**
 * @brief 构造所有AST节点的基类，其中用指针管理对象
 * 
 */

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual llvm::Value* codeGen(IRGenerator& IRContext) =0;
};

class FunctionAST : public BaseAST {
public:
    string funcname; 
    VarType type; 
    
    FunctionAST(string type, string funcname) {
        this->funcname = funcname; 
        this->type = VarType(type).GetType()
    }
    ~FunctionAST(){};
    llvm::Value* codeGen(IRGenerator& IRContext);
};

class BlockAST : public FunctionAST {
public:
    BlockAST(){}
    ~BlockAST(){}
    llvm::Value* codeGen(IRGenerator& IRContext);
}

class StmtAST: public BlockAST {
public: 
    StmtAST(){}
    ~StmtAST(){}
    llvm::Value* codeGen(IRGenerator& IRContext);
}

class ExprAST: public StmtAST {
public: 
    int a; 
    int b; 
    char op;

    ExprAST(int a, char op, int b):a(a), b(b), op(op){};
    ~ExprAST(){};
    llvm::Value* codeGen(IRGenerator& IRContext);
}
