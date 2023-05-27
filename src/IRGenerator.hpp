/**
 * @file IRGenerator.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
    VarType type_; 
    std::string name_; 
    bool isPtr_; 

	//llvm::Function* CurFunc;
    llvm::Value* value_;

    IRVarAttr(VarType type, std::string name, llvm::Value* value, bool _isPtr_=false):
        type_(type), name_(name), value_(value), isPtr_(_isPtr_){}
};

class IRLoopAttr {
public: 
    llvm::BasicBlock* condBlock_;
    llvm::BasicBlock* iterBlock_;
    llvm::BasicBlock* exitBlock_; 

    IRLoopAttr(llvm::BasicBlock* _condBlock_, llvm::BasicBlock* _iterBlock_, llvm::BasicBlock* _exitBlock_): 
        condBlock_(_condBlock_), iterBlock_(_iterBlock_), exitBlock_(_exitBlock_){}
};

class IRFuncAttr {
public: 
    llvm::FunctionType* type_; 
    std::string name_; 

	llvm::Function* func_;
    bool isDefined_; 

    IRFuncAttr(llvm::FunctionType* type, std::string name, llvm::Function* func, bool isDefined = false):
        type_(type), name_(name), func_(func), isDefined_(isDefined){}

    std::string getName() {return this->name_;}
    llvm::Function* getFunc() {return this->func_;}
    void setDefined() {this->isDefined_ = true;}
    bool getDefined() {return this->isDefined_; }
};

class IRGenerator {
public: 
    llvm::LLVMContext* Context;
    llvm::IRBuilder<>* IRBuilder;
    llvm::Module* Module;

    llvm::Function* curFunc_;
    BlockAST* curBasicBlock_;
    bool bbCreatePreBrSignal_;
    std::vector<IRVarAttr*> varList_;
    std::vector<IRFuncAttr*> funcList_;
    std::vector<IRLoopAttr*> loopLevel_; 
    std::vector<IRVarAttr*> varListForFuture_;

    IRGenerator(){
        Context = new llvm::LLVMContext; 
        IRBuilder = new llvm::IRBuilder<>(*Context);
        Module = new llvm::Module("main", *Context);

        bbCreatePreBrSignal_ = true; 
        curBasicBlock_ = NULL; 
        curFunc_ = NULL;
    }
    // ~IRGenerator(){
    //     delete Context;
    //     delete IRBuilder;
    //     delete Module;
    // }

    void GenerateCode(BaseAST*);
    void GenObjectCode(std::string);

    void CreateVar(VarType type, std::string name, llvm::Value* value, bool isPtr=false);
    void DiscardVar(); 
	llvm::Value* FindVar(std::string name);
    bool IsPtrVar(std::string name);

    void RemainFutureVar(VarType type, std::string name, llvm::Value* value, bool isPtr=false); 
    void CreateFutureVars(); 

    void SetCurFunc(llvm::Function* curFunc);
    llvm::Function* GetCurFunc();

    void SetPreBrSignal();
    bool ClearPreBrSignal();
    bool GetPreBrSignal();

    BlockAST* GetBasicBlock();
    void SetBasicBlock(BlockAST*);

    void EnterLoop(llvm::BasicBlock* condBlock, llvm::BasicBlock* iterBlock, llvm::BasicBlock* exitBlock); 
    void LeaveCurrentLoop(); 
    llvm::BasicBlock* BreakCurrentLoop(); 
    llvm::BasicBlock* ContinueCurrentLoop();

    void CreateFunc(llvm::FunctionType*, std::string name, llvm::Function* func, bool isDefined);
    void DiscardFunc(int cnt);
    llvm::Function* FindFunction(std::string Name);
    bool IsFuncDefined(std::string Name);
    bool SetFuncDefined(std::string Name); 
    // llvm::Function* CallFunction(std::string Name);
};


llvm::Value* TypeCasting(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext);

llvm::Value* TypeUpgrading(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext);