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
 * @brief 声明所有类
 * 
 */
class BaseAST; 
class FunctionAST; 
class BlockAST; 
class StmtAST; 
class ExprAST; 

/**
 * @brief 构造所有AST节点的基类，其中用指针管理对象
 * 
 */

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual llvm::Value* IRGen(IRGenerator& IRContext) =0;
};

class FunctionAST : public BaseAST {
public:
    string funcname; 
    VarType type; 
    BlockAST* blockast
    
    FunctionAST(string type, string funcname, BlockAST* blockast) {
        this->funcname = funcname; 
        this->type = VarType(type).GetType()
        this->blockast = blockast; 
    }
    ~FunctionAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
};

class BlockAST : public BaseAST {
public:
    StmtAST* stmtast;

    BlockAST(StmtAST* stmtast): stmtast(stmtast){}
    ~BlockAST(){}
    llvm::Value* IRGen(IRGenerator& IRContext);
}

class StmtAST: public BaseAST {
public: 
    ExprAST* exprast;

    StmtAST(ExprAST* exprast): exprast(exprast){}
    ~StmtAST(){}
    llvm::Value* IRGen(IRGenerator& IRContext);
}

class ExprAST: public BaseAST {
public: 
    int a; 
    int b; 
    char op;

    ExprAST(int a, char op, int b):a(a), b(b), op(op){};
    ~ExprAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
}
