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

class DeclAST;
class VarInitAST;
class VarDeclAST;
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
 * @brief 变量声明相关
 * 
 */


/* 定义声明的抽象类作为一般声明和const的基类
 * 
 */
class DeclAST : public CompUnitAST {
public:
	DeclAST() {}
	~DeclAST() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

// class VarDeclAST : public DeclAST {
// public:
// 	VarInitAST* varInit_;
// 	VarType* type_;

// 	VarDeclAST(VarInitAST* _varInit_, VarType* _type_) : 
// 		varInit_(_varInit_), type_(_type_) {}
// 	~VarDeclAST() {}

// 	llvm::Value* IRGen(IRGenerator& IRContext) {}
// };

// class VarInitAST : public BaseAST {
// public:
// 	std::string varName_;
// 	ExprAST* initExpr_;

// 	VarInitAST(std::string _varName_) : 
// 		varName_(_varName_) {}
// 	VarInitAST(std::string _varName_, ExprAST* _initExpr_) : 
// 		varName_(_varName_), initExpr_(_initExpr_) {}
// 	~VarInitAST() {}
// 	llvm::Value* IRGen(IRGenerator& IRContext) {}
// };

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

	ReturnStmtAST(ExprAST* _RetVal_ = NULL) : RetVal_(_RetVal_) {}
	~ReturnStmtAST () {}

	llvm::Value* IRGen(IRGenerator& IRContext);
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


/**
 * @brief 算术运算
 * 
 */

class MoncPlus : public ExprAST {
public:
	ExprAST* RHS_;

	MoncPlus(ExprAST* _RHS_) : RHS_(_RHS_) {}
	~MoncPlus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class MoncMinus : public ExprAST {
public:
	ExprAST* RHS_;

	MoncMinus(ExprAST* _RHS_) : RHS_(_RHS_) {}
	~MoncMinus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Addition : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Addition(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Addition() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Subtraction : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Subtraction(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Subtraction() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Multiplication : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Multiplication(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Multiplication() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Division : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Division(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Division() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Modulation : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Modulation(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Modulation() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};


/**
 * @brief 逻辑运算
 * 
 */
class LogicNot : public ExprAST {
public:
	ExprAST* RHS_;

	LogicNot(ExprAST* _RHS_) : RHS_(_RHS_) {}
	~LogicNot() {}

	llvm::Value* IRGen(IRGenerator& IRContext);

};

class AndOp : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	AndOp(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~AndOp() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class OrOp : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	OrOp(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~OrOp() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Equal : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Equal(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Equal() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class NotEqual : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	NotEqual(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~NotEqual() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class GreEqu : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	GreEqu(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~GreEqu() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LessEqu : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	LessEqu(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LessEqu() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class GreThan : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	GreThan(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~GreThan() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LessThan : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	LessThan(ExprAST* _LHS_, ExprAST* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LessThan() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Assign : public ExprAST {
public:
	ExprAST* LHS_;
	ExprAST* RHS_;

	Assign(ExprAST* _LHS_, ExprAST* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~Assign() {}

	llvm::Value* IRGen(IRGenerator& IRContext) {}
};

class Constant : public ExprAST {
public:
	int int_;

	Constant(int _int_) : int_(_int_) {}
	~Constant() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Variable : public  ExprAST {
public:
	std::string name_;

	Variable(std::string& _name_) : name_(_name_) {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};