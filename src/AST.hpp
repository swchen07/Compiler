/**
 * @file AST.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

class IRGenerator;

/**
 * @brief type类型的id
 * 
 */

enum TypeID{
    Int, 
    Char
};

class VarType {
public:
    VarType(int) {type=Int;}
    VarType(char) {type=Char;}
    VarType(std::string name) {
        if (name == "int") type = Int; 
        else if (name == "char") type = Char; 
    } 
    ~VarType(){}
    TypeID GetType() {return type;}
private: 
    TypeID type;
};

/**
 * @brief 声明所有类
 * 
 */

class BaseAST;
class ProgramAST;
class CompUnitAST;
class FuncDef;
class BlockAST;
class StmtAST;
class ReturnStmtAST;
class ExprAST;
class Addition;

using CompUnits = std::vector<CompUnitAST*>;
using Stmts = std::vector<StmtAST*>;
/**
 * @brief 构造所有AST节点的基类，其中用指针管理对象
 * 
 */

// 所有 AST 的基类
class BaseAST {
public:
	BaseAST() {}
    ~BaseAST() {}

    virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class ProgramAST : public BaseAST {
public:
	CompUnits* compUnit_;
    
    ProgramAST(CompUnits* _compUnit_):compUnit_(_compUnit_){}
    ~ProgramAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
};

/**
 * @brief ComUnit抽象类
 * 
 */
class CompUnitAST : public BaseAST {
public:
	CompUnitAST(){}
	~CompUnitAST(){}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class FuncDefAST : public CompUnitAST {
public:
	std::string funcName_; 
    VarType type_; 
    BlockAST* block_;

	FuncDefAST(std::string _typeName_, std::string _funcName_, BlockAST* _block_):funcName_(_funcName_), 
	type_(_typeName_), block_(_block_) {}

	~FuncDefAST(){};
    llvm::Value* IRGen(IRGenerator& IRContext);
};

class BlockAST : public BaseAST {
public:
    Stmts* stmts_;

    BlockAST(Stmts* _stmts_): stmts_(_stmts_){}
    ~BlockAST(){}

    llvm::Value* IRGen(IRGenerator& IRContext);
};


/**
 * @brief Statement抽象类
 * 
 */
class StmtAST: public BaseAST {
public: 
	StmtAST() {}
	~StmtAST() {}

    virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class ReturnStmtAST : public StmtAST {
public:
	ExprAST* RetVal_;

	llvm::Value* IRGen(IRGenerator& IRContext);

	ReturnStmtAST(ExprAST* _RetVal_ = NULL) : RetVal_(_RetVal_) {}
	~ReturnStmtAST () {}
};


/**
 * @brief expression抽象类
 * 
 */
class ExprAST : public BaseAST {
public:
	ExprAST(void) {}
	~ExprAST(void) {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class Addition : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Addition(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Addition() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Assign : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Assign(ExprAST* _LHS_, ExprAST* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~Assign() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Constant : public ExprAST {
public:
	int int_;

	Constant(int _int_) : int_(_int_) {}
	~Constant() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};