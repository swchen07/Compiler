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
		case Ptr: return this->_BaseType_pointer->ToLLVMType(IRContext);
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

	if (IRContext.GetCurFunc()) {
		// local variable

		auto IRBuilder = IRContext.IRBuilder; 

		//创建变量
		auto AllocMem = IRBuilder->CreateAlloca(this->type_.ToLLVMType(IRContext), 0, this->varDef_->varName_);
		
		// llvm::Value* initVal = CastType(this->, IRContext)

		// initialize
		llvm::Value* value = this->varDef_->IRGen(IRContext);

		// store will always align to 4, even for char, which is because we need a type cast for 'value'
		IRBuilder->CreateStore(value, AllocMem);

		IRContext.CreateVar(this->type_, this->varDef_->varName_, AllocMem);
	}
	else {
		// global variable
		// initialize
		std::cout << "VarDeclAST -> global variable" << std::endl;

		llvm::Value* value = this->varDef_->IRGen(IRContext);

		// convert to const
		llvm::Constant* initializer = llvm::cast<llvm::Constant>(value);
		if (!initializer) {
			throw std::logic_error("The initializer is not const type: "+this->varDef_->varName_);
		}

		//Create a global variable
		auto AllocMem = new llvm::GlobalVariable(
			*(IRContext.Module),
			this->type_.ToLLVMType(IRContext),
			false,
			llvm::Function::ExternalLinkage,
			initializer, 
			this->varDef_->varName_
		);
		
		IRContext.CreateVar(this->type_, this->varDef_->varName_, AllocMem);
	}

	return NULL;
}

llvm::Value* VarDefAST::IRGen(IRGenerator& IRContext) {
	std::cout << "VarDefAST" << std::endl;
	
	if (this->initValue_) {
		return this->initValue_->IRGen(IRContext);
	}
	else {
		auto IRBuilder = IRContext.IRBuilder; 
		return IRBuilder->getInt8(0);
	}
}

llvm::Value* ArrDefAST::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrDefAST" << std::endl;

	//获取数组元素
	this->elementType_ = this->type_.ToLLVMType(IRContext);

	llvm::Type* elementType = this->elementType_;

	//数组构造
	llvm::Type* arrayType = elementType;

	//获取数组维度
	for(auto expr : *(this->exprs_)){
		//处理expr
		llvm::Value* val = expr->IRGen(IRContext);
		//由于是从constant转换出来的，所以可以转换为constant
		llvm::ConstantInt* constant = llvm::dyn_cast<llvm::ConstantInt>(val);
		//转换完之后将int提取出来
		int convertedValue = constant->getSExtValue();
		arrayType = llvm::ArrayType::get(arrayType, convertedValue);
		// std::cout << convertedValue << "  " << std::endl;
	}

	this->arrayType_ = arrayType;
	if(IRContext.GetCurFunc()){
		auto IRBuilder = IRContext.IRBuilder;
		
		// //创建变量
		auto AllocMem = IRBuilder->CreateAlloca(this->arrayType_, 0, this->arrName_);

		//初始化
		IRContext.CreateVar(this->type_, this->arrName_, AllocMem, true); 
	}else{
		llvm::Type* intType = this->type_.ToLLVMType(IRContext);
		llvm::ArrayType* arrayType = llvm::ArrayType::get(intType, 100);
		llvm::Constant* Initializer = NULL;
		Initializer = llvm::UndefValue::get(arrayType);

		auto AllocMem = new llvm::GlobalVariable(
			*(IRContext.Module),
			arrayType,
			false,
			llvm::Function::ExternalLinkage,
			Initializer, 
			this->arrName_
		);
		
		IRContext.CreateVar(this->type_, this->arrName_, AllocMem, true);
	}
	
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
	
    //Get function type
    llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, this->_ArgList->_VarArgLenth);

	if (this->block_) {
		// define function
		if (IRContext.IsFuncDefined(this->funcName_)) {
			throw std::logic_error("Function redeclared: "+this->funcName_);
		}

		llvm::Function* Func = IRContext.FindFunction(this->funcName_);
		if (Func) {
			IRContext.SetFuncDefined(this->funcName_); 
		}
		else {
			Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);
			IRContext.CreateFunc(FuncType, this->funcName_, Func, true);
		}

		int i = 0; 
		for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++) {
			auto ArgInf = this->_ArgList->at(i);
			IRContext.RemainFutureVar(ArgInf->type_, ArgInf->_Name, ArgIter);
			i ++; 
		}

		IRContext.SetCurFunc(Func);
		IRContext.ClearPreBrSignal();

		this->block_->IRGen(IRContext);

		IRContext.SetBasicBlock(NULL); 
		IRContext.SetCurFunc(NULL); 

	}
	else {
		// declare function
		if (IRContext.FindFunction(this->funcName_)) {
			// no need to declare again
			return NULL; 
		}
		llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);

		IRContext.CreateFunc(FuncType, this->funcName_, Func, false);
	}
	
    return NULL;
}

llvm::Value* FuncCallAST::IRGen(IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.FindFunction(this->_FuncName);
	

	if (Func == NULL) {
		throw std::domain_error(this->_FuncName + " is not a defined function.");
		return NULL;
	}
	
	if (Func->isVarArg() && this->_ArgList->size() < Func->arg_size() ||
		!Func->isVarArg() && this->_ArgList->size() != Func->arg_size()) {
		throw std::invalid_argument("Args doesn't match when calling function " + this->_FuncName + ". Expected " + std::to_string(Func->arg_size()) + ", got " + std::to_string(this->_ArgList->size()));
		return NULL;
	}
	
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

	// at the beginning of a function, we need to create variables for params
	IRContext.CreateFutureVars(); 

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

    return newBlock; 
}

llvm::Value* ReturnStmtAST::IRGen(IRGenerator& IRContext) {
    std::cout << "ReturnAST" << std::endl;
    auto IRBuilder = IRContext.IRBuilder; 
	if (this->RetVal_)
    	IRBuilder->CreateRet(this->RetVal_->IRGen(IRContext));
	else
		IRBuilder->CreateRetVoid();
    return NULL; 
}

llvm::Value* IfElseStmtAST::IRGen(IRGenerator& IRContext) {
	std::cout << "IfElseStmtAST" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 

	auto CondExpr = this->cond_->IRGen(IRContext);
	llvm::BasicBlock* CondBlock = IRBuilder->GetInsertBlock();

	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* IfBlock = (llvm::BasicBlock*)this->ifBlock_->IRGen(IRContext);
	llvm::BasicBlock* IfOutBlock = IRBuilder->GetInsertBlock(); 
	llvm::BasicBlock* ElseBlock, *ElseOutBlock; 
	if (this->elseBlock_) {
		IRContext.ClearPreBrSignal();
		ElseBlock = (llvm::BasicBlock*)this->elseBlock_->IRGen(IRContext);
		ElseOutBlock = IRBuilder->GetInsertBlock(); 
	}

	// set exit 
	llvm::Function* Func = IRContext.GetCurFunc();
	llvm::BasicBlock* OutBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBExit", Func);
	IRBuilder->SetInsertPoint(IfOutBlock);
	IRBuilder->CreateBr(OutBlock);
	if (this->elseBlock_) {
		IRBuilder->SetInsertPoint(ElseOutBlock);
		IRBuilder->CreateBr(OutBlock);
	}

	// set conditional branch
	IRBuilder->SetInsertPoint(CondBlock);
	IRBuilder->CreateCondBr(CondExpr, IfBlock, this->elseBlock_?ElseBlock:OutBlock);

	IRBuilder->SetInsertPoint(OutBlock);

	return NULL;
}

llvm::Value* ForStmtAST::IRGen(IRGenerator& IRContext) {
	std::cout << "ForStmtAST" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.GetCurFunc();

	// init generate
	if (this->initStmt_)
		this->initStmt_->IRGen(IRContext); 
	llvm::BasicBlock* cmpBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForCmp", Func);
	llvm::BasicBlock* iterBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForIter", Func);
	llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForExit", Func);
	IRBuilder->CreateBr(cmpBlock);
	// enter the Loop
	IRContext.EnterLoop(cmpBlock, iterBlock, exitBlock); 

	// condition generate
	IRBuilder->SetInsertPoint(cmpBlock);
	auto cmpRes = (this->condExpr_)?this->condExpr_->IRGen(IRContext):IRBuilder->getInt1(true); 

	// body generate
	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* bodyBlock = (llvm::BasicBlock*)this->forBody_->IRGen(IRContext);
	llvm::BasicBlock* bodyOutBlock = IRBuilder->GetInsertBlock();

	// iteration generate
	IRBuilder->CreateBr(iterBlock);
	IRBuilder->SetInsertPoint(iterBlock);
	if (this->iterStmt_) this->iterStmt_->IRGen(IRContext);
	IRBuilder->CreateBr(cmpBlock);

	// set conditional branch
	IRBuilder->SetInsertPoint(cmpBlock);
	IRBuilder->CreateCondBr(cmpRes, bodyBlock, exitBlock);

	// leave the Loop
	IRContext.LeaveCurrentLoop(); 
	IRBuilder->SetInsertPoint(exitBlock);

	return NULL;
}


llvm::Value* WhileStmtAST::IRGen(IRGenerator& IRContext) {
	std::cout << "WhileStmtAST" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.GetCurFunc();

	// init
	llvm::BasicBlock* cmpBlock = llvm::BasicBlock::Create(*(IRContext.Context), "WhileCmp", Func);
	llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*(IRContext.Context), "WhileExit", Func);
	IRBuilder->CreateBr(cmpBlock);
	// enter the Loop
	IRContext.EnterLoop(cmpBlock, NULL, exitBlock); 

	// condition generate
	IRBuilder->SetInsertPoint(cmpBlock);
	auto cmpRes = (this->condExpr_)?this->condExpr_->IRGen(IRContext):IRBuilder->getInt1(true); 

	// body generate
	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* bodyBlock = (llvm::BasicBlock*)this->whileBody_->IRGen(IRContext);
	llvm::BasicBlock* bodyOutBlock = IRBuilder->GetInsertBlock();
	IRBuilder->CreateBr(cmpBlock);

	// set conditional branch
	IRBuilder->SetInsertPoint(cmpBlock);
	IRBuilder->CreateCondBr(cmpRes, bodyBlock, exitBlock);

	// leave the Loop
	IRContext.LeaveCurrentLoop(); 
	IRBuilder->SetInsertPoint(exitBlock);

	return NULL;
}

llvm::Value* BreakStmtAST::IRGen(IRGenerator& IRContext) {
	std::cout << "BreakStmtAST" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::BasicBlock* targetBlock = IRContext.BreakCurrentLoop();
	IRBuilder->CreateBr(targetBlock);

	return NULL; 
}

llvm::Value* ContinueStmtAST::IRGen(IRGenerator& IRContext) {
	std::cout << "ContinueStmtAST" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::BasicBlock* targetBlock = IRContext.ContinueCurrentLoop();
	IRBuilder->CreateBr(targetBlock);

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
	return RHS; 

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
	if (IRContext.IsPtrVar(this->name_)) {
		return VarPtr; 
	}
	else {
		llvm::Type* type = VarPtr->getType()->getNonOpaquePointerElementType();
		llvm::Value* val = IRBuilder->CreateLoad(type,VarPtr);
		return val;
	}
}

llvm::Value* LeftValAST::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "LeftValPtr" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	return VarPtr;
}

llvm::Value* StringType::IRGen(IRGenerator& IRContext) {
    std::cout << "StringType" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	return IRBuilder->CreateGlobalStringPtr(this->_Content.c_str());
}

llvm::Value* AddressOf::IRGen(IRGenerator& IRContext) {
    std::cout << "AddressOf" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->_Operand->name_);
	return VarPtr;
}

// llvm::Value* ArrValAST::IRGen(IRGenerator& IRContext) {
// 	std::cout << "ArrVal" << std::endl;

// 	auto IRBuilder = IRContext.IRBuilder;

// 	//搜索数组的指针
// 	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	
// 	//this->exprs_ index索引

// 	std::vector<llvm::Value*> indices;

// 	//生成每个维度的索引

// 	for(auto expr : *(this->exprs_)){
// 		indices.push_back(expr->IRGen(IRContext));

// 	}

// 	llvm::Value* v1, *v2;

// 	for(auto indice: indices){
// 		if(arrayPtr->getType()->isArrayTy()){
// 			v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
// 		}
// 		else if(arrayPtr->getType()->isPointerTy()){
// 			v1 = arrayPtr;
// 		}
// 		else{
// 			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
// 		}
// 		if(indice->getType()->isIntegerTy()){
// 			v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
// 		}
// 		else{
// 			throw std::logic_error("The sunsciption operation received not integer");
// 		}
// 	}
	
// 	// llvm::Value* v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

// 	// llvm::Value* v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indices[0]);
	
// 	return IRBuilder->CreateLoad(v1->getType()->getNonOpaquePointerElementType(), v2);

// }

llvm::Value* ArrValAST::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrVal" << std::endl;

	auto IRBuilder = IRContext.IRBuilder;

	//搜索数组的指针
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	// auto* arrayPtr = IRContext.Module->getGlobalVariable(this->name_);
	std::cout << "Array Ptr " << arrayPtr << std::endl; 
	
	//this->exprs_ index索引

	std::vector<llvm::Value*> indices;

	//生成每个维度的索引

	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));

	}

	llvm::Value* v1, *v2;

	for(auto indice: indices){
		if(arrayPtr->getType()->getNonOpaquePointerElementType()->isArrayTy()){
			v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
		}
		else if(arrayPtr->getType()->isPointerTy()){
			v1 = IRBuilder->CreateLoad(arrayPtr->getType()->getNonOpaquePointerElementType(), arrayPtr);
		}
		else{
			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
		}
		// v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

		v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
	}
	
	// llvm::Value* v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

	// llvm::Value* v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indices[0]);
	
	return IRBuilder->CreateLoad(v1->getType()->getNonOpaquePointerElementType(), v2);

}

llvm::Value* ArrValAST::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "ArrValPtr" << std::endl;

	auto IRBuilder = IRContext.IRBuilder;

	//搜索数组的指针
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	arrayPtr->print(llvm::outs());
	std::cout << "We find the type!!!!!!!!!!!!!!" << std::endl;
	
	//this->exprs_ index索引

	std::vector<llvm::Value*> indices;

	//生成每个维度的索引

	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));

	}
	
	llvm::Value* v1, *v2;

	for(auto indice: indices){
		v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

		
		v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
	}
	v1->print(llvm::outs());
		std::cout << "We find the type!!!!!!!!!!!!!!" << std::endl;
		v2->print(llvm::outs());
		std::cout << "We find the type!!!!!!!!!!!!!!" << std::endl;
	return v2;


	// llvm::Value* zeroIndex = indices;
	// llvm::Value* oneIndex = indices;

	// // 计算第二行第二列元素的地址
	// llvm::Value* rowIndex = oneIndex;
	// llvm::Value* columnIndex = oneIndex;

	// llvm::Type* intType = IRBuilder->getInt32Ty();
	// llvm::ArrayType* arrayType = llvm::ArrayType::get(intType, 5);

	// // 第一维索引
	// llvm::Value* firstDimensionIndex = zeroIndex;

	// llvm::Value* firstDimensionPtr = IRBuilder->CreateGEP(arrayPtr->getType()->getNonOpaquePointerElementType(),arrayPtr, firstDimensionIndex);

	// // 第二维索引
	// llvm::Value* secondDimensionPtr = IRBuilder->CreateGEP(firstDimensionPtr->getType()->getNonOpaquePointerElementType(), firstDimensionPtr, rowIndex);


	// return secondDimensionPtr;
}

llvm::Value* AssignArrAST::IRGen(IRGenerator& IRContext){
	std::cout << "Assign" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);	
	llvm::Value* LHSPtr = this->LHS_->IRGenPtr(IRContext);

	//赋值
	IRBuilder->CreateStore(RHS, LHSPtr);
	return RHS; 
}

llvm::Type* PointerType::ToLLVMType(IRGenerator& IRContext){
	std::cout << "PointerType" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Type* BaseType = this->_BaseType.ToLLVMType(IRContext);
	return llvm::PointerType::get(BaseType, 0U);
}