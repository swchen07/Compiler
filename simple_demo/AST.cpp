/**
 * @file AST.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "IRGenerator.hpp"

// extern llvm::IRBuilder<> IRBuilder; 

llvm::Value* ProgramAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ProgramAST" << std::endl;
    // IRContext.Module->print(llvm::outs(), NULL);
    this->funcast->IRGen(IRContext); 
    return NULL; 
}

llvm::Value* FunctionAST::IRGen(IRGenerator& IRContext) {
    //Get return type
    std::cout << "FunctionAST" << std::endl;
    auto IRBuilder = IRContext.IRBuilder; 
    llvm::Type* ReturnType; 
    if (this->type.GetType() == Int)
        ReturnType = IRBuilder->getInt32Ty();

    std::vector<llvm::Type*> ArgTypes; 

    //Get function type
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, false);
    //Create function
    llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcname, IRContext.Module);
    // IRContext.AddFunction(this->funcname, Func);
    // IRContext.Module->print(llvm::outs(), NULL);

    this->blockast->IRGen(IRContext); 
    return NULL;
}

llvm::Value* BlockAST::IRGen(IRGenerator& IRContext) {
    std::cout << "BlockAST" << std::endl;
    this->stmtast->IRGen(IRContext); 
    return NULL; 
}

llvm::Value* StmtAST::IRGen(IRGenerator& IRContext) {
    std::cout << "StmtAST" << std::endl;
    auto IRBuilder = IRContext.IRBuilder; 
    IRBuilder->CreateRet(this->exprast->IRGen(IRContext));
    return NULL; 
}

llvm::Value* ExprAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST" << std::endl;
    if (this->op == '+') {
        std::cout << "ExprAST+" << std::endl;
        auto IRBuilder = IRContext.IRBuilder; 
        return IRBuilder->CreateAdd(IRBuilder->getInt32(this->a), IRBuilder->getInt32(this->b));
    }
    else {
        printf("Error!"); 
        return NULL;
    }
}