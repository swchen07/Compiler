#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
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
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/MC/TargetRegistry.h>


#include "AST.hpp"

class IRVarAttr {
public: 
    TypeID type_; 
    std:string name_; 

	//llvm::Function* CurFunc;
    llvm::Value* value_;

    IRVarAttr(TypeID type, std::string name, llvm::Value* value):type_(type), name_(name), value_(value){}
};

class IRGenerator {
public: 
    llvm::LLVMContext* Context;
    llvm::IRBuilder<>* IRBuilder;
    llvm::Module* Module;

    std::vector<IRVarAttr*> varList_;
    llvm::Function* curFunc_;

    IRGenerator(){
        Context = new llvm::LLVMContext; 
        IRBuilder = new llvm::IRBuilder<>(*Context);
        Module = new llvm::Module("main", *Context);
    }
    // ~IRGenerator(){
    //     delete Context;
    //     delete IRBuilder;
    //     delete Module;
    // }

    void GenerateCode(BaseAST*);
    void GenObjectCode(std::string);
    void CreateVar(TypeID type, std::string name, llvm::Value* value);
    void DiscardVar(int cnt); 
    void SetCurFunc(llvm::Function* curFunc);
    llvm::Function* GetCurFunc();
};