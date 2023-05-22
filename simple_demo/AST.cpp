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

#include "AST.hpp"
#include "IRGenerator.hpp"
#include <cstdio>

llvm::Value* FunctionAST::IRGen(IRGenerator& IRContext) {
    //Get return type
    llvm::Type* ReturnType = this->_RetType->GetLLVMType(__Generator);

    //Get function type
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, NULL, NULL);
    //Create function
    llvm::Function* Func = llvm::Function::Create(FuncType, llvm::GlobalValue::ExternalLinkage, this->_Name, __Generator.Module);
    __Generator.AddFunction(this->_Name, Func);
}

llvm::Value* BlockAST::IRGen(IRGenerator& IRContext) {
    return this->stmtast->IRGen(IRContext); 
}

llvm::Value* StmtAST::IRGen(IRGenerator& IRContext) {
    auto IRBuilder = IRContext.IRBuilder; 
    IRBuilder->CreateRet(this->exprast->IRGen(IRContext));
    return NULL; 
}

llvm::Value* ExprAST::IRGen(IRGenerator& IRContext) {
    if (this->op == '+') {
        auto IRBuilder = IRContext.IRBuilder; 
        return IRBuilder->CreateAdd(IRBuilder->getInt32(this->a), IRBuilder->getInt32(this->b));
    }
    else {
        printf("Error!"); 
        return NULL;
    }
}