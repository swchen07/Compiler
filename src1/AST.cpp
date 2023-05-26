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
#include "utils.hpp"


/**
 * @brief 考虑到逻辑运算中需要用到true or false的判断
 * 通过该函数把类型转换成bool型（即1bit）
 * 
 */
llvm::Value* ToBoolType(llvm::Value* value, IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder; 
	if (value->getType() == IRBuilder->getInt1Ty()) return value;
	else if (value->getType()->isIntegerTy()){
		auto v2 = llvm::ConstantInt::get((llvm::IntegerType*)value->getType(), 0, true);
		return IRBuilder->CreateICmpNE(value, v2);
	}else{
		return NULL;
	}
}

/**
 * @brief 涉及到类型转换
 * 目前支持：
 * 1. 类型相同
 * 2. 转换成bool
 * 
 */
llvm::Value* CastType(llvm::Value* value, llvm::Type* type, IRGenerator& IRContext){
	auto IRBuilder = IRContext.IRBuilder;
	if(value->getType() == type){
		return value;
	}else if(type == IRBuilder->getInt1Ty()){
		return ToBoolType(value, IRContext);
	}
	// else if(value=>get){

	// }
}
/**
 * @brief 
 * 
 * 
 */

VarType::VarType(std::string name) {
	if (name == "int") type = Int; 
	else if (name == "char") type = Char; 
	else if (name == "short") type = Short;
} 

llvm::Type* VarType::ToLLVMType(IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder;
	switch(this->type) {
		case Int: return IRBuilder->getInt32Ty(); 
		case Char: return IRBuilder->getInt8Ty(); 
		case Short: return IRBuilder->getInt16Ty(); 
	}
}

/**
 * @brief 
 * 
 * 
 */


llvm::Value* ProgramAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ProgramAST" << std::endl;

	for (auto compUnit : *(this->compUnit_)){
		if(compUnit){
			compUnit->IRGen(IRContext);
		}
	}

	return NULL;
}

llvm::Value* VarDeclAST::IRGen(IRGenerator& IRContext) {
	std::cout << "VarDeclAST" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 

	//创建变量
	auto AllocMem = IRBuilder->CreateAlloca(this->type_.ToLLVMType(IRContext), 0, this->varDef_->varName_);
	
	// llvm::Value* initVal = CastType(this->, IRContext)

	// initializa
	llvm::Value* value = this->varDef_->IRGen(IRContext);

	IRBuilder->CreateStore(value, AllocMem);

	IRContext.CreateVar(this->type_, this->varDef_->varName_, AllocMem);

	return NULL;
}

llvm::Value* VarDefAST::IRGen(IRGenerator& IRContext) {
	std::cout << "VarDefAST" << std::endl;
	
	if (this->initValue_) {
		return this->initValue_->IRGen(IRContext);
	}
	else {
		auto IRBuilder = IRContext.IRBuilder; 
		return IRBuilder->getInt8('0');
	}
}

llvm::Value* BlockAST::IRGen(IRGenerator& IRContext) {
    std::cout << "BlockAST" << std::endl;

	// // Empty Block
	// if (this->stmts_.size() == 0) {
	// 	IRContext.SetPreBrSignal();
	// 	return NULL; 
	// }

	auto IRBuilder = IRContext.IRBuilder; 

	llvm::Function* Func = IRContext.GetCurFunc();
	llvm::BasicBlock* newBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBEntry", Func);
	auto prevBB = IRContext.GetBasicBlock(); 

	bool isConn = IRContext.ClearPreBrSignal(); 
	if (isConn) {
		// maybe go into a function, thus not insert Br
		IRBuilder->CreateBr(newBlock);
	}
	IRContext.SetPreBrSignal();

	IRContext.SetBasicBlock(this); 
    IRBuilder->SetInsertPoint(newBlock);

	for (auto stmt : *(this->stmts_)){
		if(stmt){
			stmt->IRGen(IRContext);
		}
	}

	IRContext.DiscardVar();

	IRContext.SetBasicBlock(prevBB); 
	if (isConn) {
		llvm::BasicBlock* outBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBExit", Func);
		IRBuilder->CreateBr(outBlock);
		IRBuilder->SetInsertPoint(outBlock);
	}

    return NULL; 
}

llvm::Value* ReturnStmtAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ReturnAST" << std::endl;
    auto IRBuilder = IRContext.IRBuilder; 
    IRBuilder->CreateRet(this->RetVal_->IRGen(IRContext));
    return NULL; 
}


/**
 * @brief 算术运算
 * 
 */
llvm::Value* MoncPlus::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST +1" << std::endl;
	llvm::Value* val = this->RHS_->IRGen(IRContext);
	return val;

}

llvm::Value* MoncMinus::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST -1" << std::endl;
	llvm::Value* val = this->RHS_->IRGen(IRContext);
	auto IRBuilder = IRContext.IRBuilder; 
	return IRBuilder->CreateNeg(val);

}

llvm::Value* Addition::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST +" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateAdd(LHS, RHS);
}

llvm::Value* Subtraction::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST -" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateSub(LHS, RHS);
}

llvm::Value* Multiplication::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST *" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateMul(LHS, RHS);
}

llvm::Value* Division::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST /" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateSDiv(LHS, RHS);
}

llvm::Value* Modulation::IRGen(IRGenerator& IRContext) {
    std::cout << "ExprAST %" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateSRem(LHS, RHS);
}


/**
 * @brief 逻辑运算
 * 
 */
llvm::Value* LogicNot::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST !" << std::endl;
	llvm::Value* val = this->RHS_->IRGen(IRContext);
	auto IRBuilder = IRContext.IRBuilder;
	return IRBuilder->CreateICmpEQ(ToBoolType(val, IRContext), IRBuilder->getInt1(false));
}

llvm::Value* AndOp::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST &&" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext), IRContext);
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext), IRContext);
	return IRBuilder->CreateLogicalAnd(LHS, RHS);
}

llvm::Value* OrOp::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST ||" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext), IRContext);
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext), IRContext);
	return IRBuilder->CreateLogicalOr(LHS, RHS);
}

llvm::Value* Equal::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST ==" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpEQ(LHS, RHS);
}

llvm::Value* NotEqual::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST !=" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpNE(LHS, RHS);
}

llvm::Value* GreThan::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST >" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSGT(LHS, RHS);
}

llvm::Value* LessThan::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST >" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLT(LHS, RHS);
}

llvm::Value* GreEqu::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST >" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSGE(LHS, RHS);
}

llvm::Value* LessEqu::IRGen(IRGenerator& IRContext) {
	std::cout << "ExprAST >" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLE(LHS, RHS);
}

llvm::Value* AssignAST::IRGen(IRGenerator& IRContext){
	std::cout << "Assign" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	llvm::Value* LHSPtr = this->LHS_->IRGenPtr(IRContext);

	//赋值
	IRBuilder->CreateStore(RHS, LHSPtr);
	return IRBuilder->CreateLoad(LHSPtr->getType()->getNonOpaquePointerElementType(), LHSPtr);

}

llvm::Value* Constant::IRGen(IRGenerator& IRContext) {
	std::cout << "Constant" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	return IRBuilder->getInt32(this->int_);
}

llvm::Value* LeftValAST::IRGen(IRGenerator& IRContext) {
	std::cout << "LeftVal" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	llvm::Type* type = VarPtr->getType()->getNonOpaquePointerElementType();
	llvm::Value* val = IRBuilder->CreateLoad(type,VarPtr);
	return val;
}

llvm::Value* LeftValAST::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "LeftValPtr" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	return VarPtr;
}


llvm::Value* FuncDefAST::IRGen(IRGenerator& IRContext) {
    //Get return type
    std::cout << "FunctionAST" << std::endl;

    auto IRBuilder = IRContext.IRBuilder; 
    llvm::Type* ReturnType = this->type_.ToLLVMType(IRContext);

    std::vector<llvm::Type*> ArgTypes; 
	for (auto ArgType : *(this->_ArgList)) {
		llvm::Type* LLVMType = ArgType->type_.ToLLVMType(IRContext);
		if (!LLVMType) {
			throw std::logic_error("Defining a function " + this->funcName_ + " using unknown type(s).");
			return NULL;
		}
		ArgTypes.push_back(LLVMType);
	}
	
    std::cout << "xx" << std::endl;
	
    //Get function type
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, this->_ArgList->_VarArgLenth);
    //Create function
    llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);

	IRContext.CreateFunc(FuncType, this->funcName_, Func);

	if(this->block_){
		IRContext.SetCurFunc(Func);
		IRContext.ClearPreBrSignal();

		this->block_->IRGen(IRContext);

		IRContext.SetBasicBlock(NULL); 
		IRContext.SetCurFunc(NULL); 
	}
	
    return NULL;
}

llvm::Value* FunctionCallAST::IRGen(IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.FindFunction(this->_FuncName);
	//Get the function. Throw exception if the function doesn't exist.
	if (Func == NULL) {
		throw std::domain_error(this->_FuncName + " is not a defined function.");
		return NULL;
	}
	//Check the number of args. If Func took a different number of args, reject.
	if (Func->isVarArg() && this->_ArgList->size() < Func->arg_size() ||
		!Func->isVarArg() && this->_ArgList->size() != Func->arg_size()) {
		throw std::invalid_argument("Args doesn't match when calling function " + this->_FuncName + ". Expected " + std::to_string(Func->arg_size()) + ", got " + std::to_string(this->_ArgList->size()));
		return NULL;
	}
	//Check arg types. If Func took different different arg types, reject.
	std::vector<llvm::Value*> ArgList;
	size_t Index = 0;
	for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++, Index++) {
		llvm::Value* Arg = this->_ArgList->at(Index)->IRGen(IRContext);
		Arg = TypeCasting(Arg, ArgIter->getType(), IRContext);
		if (Arg == NULL) {
			throw std::invalid_argument(std::to_string(Index) + "-th arg type doesn't match when calling function " + this->_FuncName + ".");
			return NULL;
		}
		ArgList.push_back(Arg);
	}
	//Continue to push arguments if this function takes a variable number of arguments
	//According to the C standard, bool/char/short should be extended to int, and float should be extended to double
	if (Func->isVarArg())
		for (; Index < this->_ArgList->size(); Index++) {
			llvm::Value* Arg = this->_ArgList->at(Index)->IRGen(IRContext);
			if (Arg->getType()->isIntegerTy())
				Arg = TypeUpgrading(Arg, IRBuilder->getInt32Ty(), IRContext);
			else if (Arg->getType()->isFloatingPointTy())
				Arg = TypeUpgrading(Arg, IRBuilder->getDoubleTy(), IRContext);
			ArgList.push_back(Arg);
		}

	return IRBuilder->CreateCall(Func, ArgList);
}
