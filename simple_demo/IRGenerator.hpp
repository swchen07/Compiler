/**
 * @file IRGenerator.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>

class IRGenerator {
public: 
    llvm::LLVMContext* Context
    llvm::IRBuilder* IRBuilder;
    llvm::Module* Module;

    IRGenerator(){
        Context = new llvm::LLVMContext;
        IRBuilder = new llvm::IRBuilder<>(*Context);
        Module = new llvm::Module("main", *Context);
    }
    ~IRGenerator(){
        delete Context;
        delte IRBuilder;
        delete Module;
    }

    void GenerateCode(BaseAST*);
    void GenObjectCode(string);
}