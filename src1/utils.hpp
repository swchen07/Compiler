#pragma once
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