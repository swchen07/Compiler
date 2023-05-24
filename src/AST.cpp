/**
 * @file AST.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "IRGenerator.hpp"

llvm::Value* ProgramAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ProgramAST" << std::endl;

	for (auto compUnit : *(this->compUnit_)){
		if(compUnit){
			compUnit->IRGen(IRContext);
		}
	}

	return NULL;
}

llvm::Value* FuncDefAST::IRGen(IRGenerator& IRContext) {
    //Get return type
    std::cout << "FunctionAST" << std::endl;

    auto IRBuilder = IRContext.IRBuilder; 
    llvm::Type* ReturnType; 
    if (this->type_.GetType() == Int)
        ReturnType = IRBuilder->getInt32Ty();

    std::vector<llvm::Type*> ArgTypes; 

    //Get function type
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, false);
    //Create function
    llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);
    // IRContext.AddFunction(this->funcname, Func);
    // IRContext.Module->print(llvm::outs(), NULL);
    llvm::BasicBlock* FuncBlock = llvm::BasicBlock::Create(*(IRContext.Context), "entry", Func);
    IRBuilder->SetInsertPoint(FuncBlock);

    this->block_->IRGen(IRContext); 
    return NULL;
}

llvm::Value* BlockAST::IRGen(IRGenerator& IRContext) {
    std::cout << "BlockAST" << std::endl;
	for (auto stmt : *(this->stmts_)){
		if(stmt){
			stmt->IRGen(IRContext);
		}
	}
    return NULL; 
}

llvm::Value* ReturnStmtAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ReturnAST" << std::endl;
    auto IRBuilder = IRContext.IRBuilder; 
    IRBuilder->CreateRet(this->RetVal_->IRGen(IRContext));
    return NULL; 
}

llvm::Value* Addition::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST+" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateAdd(LHS, RHS);
        // auto IRBuilder = IRContext.IRBuilder; 
        // return IRBuilder->CreateAdd(IRBuilder->getInt32(this->a), IRBuilder->getInt32(this->b));
    
}

llvm::Value* Constant::IRGen(IRGenerator& IRContext) {
	std::cout << "Constant" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	return IRBuilder->getInt32(this->int_);
}