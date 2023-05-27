/**
 * @file IRGenerator.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "AST.hpp"
#include "IRGenerator.hpp"


llvm::Value* TypeCasting(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder; 
	if (Value->getType() == Type) {
		return Value;
	}
	else if (Type == IRBuilder->getInt1Ty()) {	//Int1 (bool) is special.
		if (Value->getType() == IRBuilder->getInt1Ty())
			return Value;
		else if (Value->getType()->isIntegerTy())
			return IRBuilder->CreateICmpNE(Value, llvm::ConstantInt::get((llvm::IntegerType*)Value->getType(), 0, true));
		else if (Value->getType()->isFloatingPointTy())
			return IRBuilder->CreateFCmpONE(Value, llvm::ConstantFP::get(Value->getType(), 0.0));
		else if (Value->getType()->isPointerTy())
			return IRBuilder->CreateICmpNE(IRBuilder->CreatePtrToInt(Value, IRBuilder->getInt64Ty()), IRBuilder->getInt64(0));
		else {
			throw std::logic_error("Cannot cast to bool type.");
			return NULL;
		}
	}
	else if (Value->getType()->isIntegerTy() && Type->isIntegerTy()) {
		return IRBuilder->CreateIntCast(Value, Type, !Value->getType()->isIntegerTy(1));
	}
	else if (Value->getType()->isIntegerTy() && Type->isFloatingPointTy()) {
		return Value->getType()->isIntegerTy(1) ?
			IRBuilder->CreateUIToFP(Value, Type) : IRBuilder->CreateSIToFP(Value, Type);
	}
	else if (Value->getType()->isIntegerTy() && Type->isPointerTy()) {
		return IRBuilder->CreateIntToPtr(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isIntegerTy()) {
		return IRBuilder->CreateFPToSI(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isFloatingPointTy()) {
		return IRBuilder->CreateFPCast(Value, Type);
	}
	else if (Value->getType()->isPointerTy() && Type->isIntegerTy()) {
		return IRBuilder->CreatePtrToInt(Value, Type);
	}
	else if (Value->getType()->isPointerTy() && Type->isPointerTy()) {
		return IRBuilder->CreatePointerCast(Value, Type);
	}
	else {
		return NULL;
	}
}

llvm::Value* TypeUpgrading(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder; 

	if (Value->getType()->isIntegerTy() && Type->isIntegerTy()) {
		size_t Bit1 = ((llvm::IntegerType*)Value->getType())->getBitWidth();
		size_t Bit2 = ((llvm::IntegerType*)Type)->getBitWidth();
		if (Bit1 < Bit2)
			return IRBuilder->CreateIntCast(Value, Type, Bit1 != 1);
		else return Value;
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isFloatingPointTy()) {
		if (Value->getType()->isFloatTy() && Type->isDoubleTy())
			return IRBuilder->CreateFPCast(Value, Type);
		else return Value;
	}
	else if (Value->getType()->isIntegerTy() && Type->isFloatingPointTy()) {
		return Value->getType()->isIntegerTy(1) ?
			IRBuilder->CreateUIToFP(Value, Type) : IRBuilder->CreateSIToFP(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isIntegerTy()) {
		return Value;
	}
	else return NULL;
}

void IRGenerator::GenerateCode(BaseAST* root) {
    root->IRGen(*this);
	this->Module->print(llvm::outs(), NULL);
}

void IRGenerator::GenObjectCode(std::string outputfile) {
	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    auto Features = "";
    auto CPU = "generic";
    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
    Module->setDataLayout(TargetMachine->createDataLayout());
    Module->setTargetTriple(TargetTriple);

    std::error_code EC;
    llvm::raw_fd_ostream Dest(outputfile, EC, llvm::sys::fs::OF_None);

    auto FileType = llvm::CGFT_ObjectFile;
    llvm::legacy::PassManager PM;
    TargetMachine->addPassesToEmitFile(PM, Dest, nullptr, FileType);

    PM.run(*Module);
    Dest.flush();
}

void IRGenerator::CreateVar(VarType type, std::string name, llvm::Value* value, bool isPtr){
    // first judge name
    int conflictCnt; 
    int varCnt = this->varList_.size(); 
    if (this->curBasicBlock_) conflictCnt = this->curBasicBlock_->varCnt_; 
    else conflictCnt = varCnt;
    for (int i = 1; i <= conflictCnt; i++) {
        if (this->varList_[varCnt-i]->name_ == name) {
            // already has the same name
            throw std::logic_error("Already Create a Variable with Name: "+name);
        }
    } 

    this->varList_.push_back(new IRVarAttr(type, name, value, isPtr));
    if (this->curBasicBlock_) this->curBasicBlock_->varCnt_ += 1; 
}

void IRGenerator::DiscardVar() {
    if (this->curBasicBlock_)
        for (int i = 0; i < this->curBasicBlock_->varCnt_; i++) {
            auto var = this->varList_[this->varList_.size()-1];
            this->varList_.pop_back();
            delete var; 
        }
}

llvm::Value* IRGenerator::FindVar(std::string name){
	if(this->varList_.size() == 0){
		return NULL;
	}
	for(auto symbol = this->varList_.end() - 1; symbol >= this->varList_.begin(); symbol--){
		if((*symbol)->name_ == name){
			return (*symbol)->value_;
		}
	}
	return NULL;
}

bool IRGenerator::IsPtrVar(std::string name) {
    if(this->varList_.size() == 0){
		return false;
	}
	for(auto symbol = this->varList_.end() - 1; symbol >= this->varList_.begin(); symbol--){
		if((*symbol)->name_ == name){
			return (*symbol)->isPtr_; 
		}
	}
	return false;
}

void IRGenerator::SetCurFunc(llvm::Function* curFunc) {
    this->curFunc_ = curFunc; 
}

llvm::Function* IRGenerator::GetCurFunc() {
    return this->curFunc_; 
}

void IRGenerator::SetPreBrSignal() {
    this->bbCreatePreBrSignal_ = true; 
}

bool IRGenerator::ClearPreBrSignal() {
    bool bbCreatePreBrSignal = this->bbCreatePreBrSignal_; 
    this->bbCreatePreBrSignal_ = false;
    return bbCreatePreBrSignal;
}

bool IRGenerator::GetPreBrSignal() {
    return this->bbCreatePreBrSignal_; 
}

BlockAST* IRGenerator::GetBasicBlock() {
    return this->curBasicBlock_; 
}

void IRGenerator::SetBasicBlock(BlockAST* newBasicBlock){
    this->curBasicBlock_ = newBasicBlock; 
}

void IRGenerator::EnterLoop(llvm::BasicBlock* condBlock, llvm::BasicBlock* iterBlock, llvm::BasicBlock* exitBlock) {
    this->loopLevel_.push_back(new IRLoopAttr(condBlock, iterBlock, exitBlock));
}

void IRGenerator::LeaveCurrentLoop() {
    this->loopLevel_.pop_back();
}

llvm::BasicBlock* IRGenerator::BreakCurrentLoop() {
    auto currentLoop = this->loopLevel_[this->loopLevel_.size()-1];
    return currentLoop->exitBlock_; 
}

llvm::BasicBlock* IRGenerator::ContinueCurrentLoop() {
    auto currentLoop = this->loopLevel_[this->loopLevel_.size()-1];
    return currentLoop->iterBlock_?currentLoop->iterBlock_:currentLoop->condBlock_; 
}

void IRGenerator::CreateFunc(llvm::FunctionType* type, std::string name, llvm::Function* func, bool isDefined){
    if(this->FindFunction(name)){
        return;
    }
    this->funcList_.push_back(new IRFuncAttr(type, name, func, isDefined));
}

void IRGenerator::DiscardFunc(int cnt) {
    for (int i = 0; i < cnt; i++) {
        auto func = this->funcList_[this->funcList_.size()-1];
		this->funcList_.pop_back();
        delete func; 
    }
}

llvm::Function* IRGenerator::FindFunction(std::string Name) {
	if (this->funcList_.size() == 0) return NULL;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == Name){
            return (*iter)->getFunc();
        }
    }
	return NULL;
}

bool IRGenerator::IsFuncDefined(std::string Name) {
	if (this->funcList_.size() == 0) return false;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == Name){
            if ((*iter)->getDefined()) return true; 
            else return false; 
        }
    }
	return false;
}

bool IRGenerator::SetFuncDefined(std::string Name) {
    if (this->funcList_.size() == 0) return false;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == Name){
            (*iter)->setDefined(); 
            return true; 
        }
    }
	return false;
}

// llvm::Function* IRGenerator::CallFunction(std::string Name) {
//     if (this->funcList_.size() == 0) {
//         throw std::logic_error("Cannot find the function: "+Name);
//         return NULL;
//     }
//     for (auto iter = this->funcList_[this->funcList_.size()-1]; iter >= this->funcList_[0]; iter--) {
//         if (iter->getName() == Name){
//             if (iter->getDefined()) 
//                 return iter->getFunc();
//             else {
//                 throw std::logic_error("Function declared but not defined: "+Name);
//                 return NULL;
//             }
//         }
//     }
//     throw std::logic_error("Cannot find the function: "+Name);
//     return NULL;
// }