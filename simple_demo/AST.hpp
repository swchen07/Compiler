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

#pragma once

#include <llvm/IR/Value.h>
#include <string>
#include <iostream>

class IRGenerator;

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
    VarType(std::string name) {
        if (name == "int") type = Int; 
        else if (name == "char") type = Char; 
    } 
    ~VarType(){}
    TypeID GetType() {return type;}
private: 
    TypeID type;
};

/**
 * @brief 声明所有类
 * 
 */
class BaseAST; 
class ProgramAST;
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

class ProgramAST : public BaseAST {
public:
    FunctionAST* funcast;  
    
    ProgramAST(FunctionAST* funcast):funcast(funcast){}
    ~ProgramAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
};

class FunctionAST : public BaseAST {
public:
    std::string funcname; 
    VarType type; 
    BlockAST* blockast;
    
    FunctionAST(std::string type_name, std::string funcname, BlockAST* blockast):funcname(funcname), type(type_name), blockast(blockast) {
        // std::cout << type_name << " " << funcname << std::endl;
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
};

class StmtAST: public BaseAST {
public: 
    ExprAST* exprast;

    StmtAST(ExprAST* exprast): exprast(exprast){}
    ~StmtAST(){}
    llvm::Value* IRGen(IRGenerator& IRContext);
};

class ExprAST: public BaseAST {
public: 
    int a; 
    int b; 
    char op;

    ExprAST(int a, char op, int b):a(a), b(b), op(op){
        // std::cout << a << " " << b << std::endl;
    };
    ~ExprAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
};