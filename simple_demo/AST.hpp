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

#include <string>
#include <iostream>

#include <llvm/IR/Value.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>

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