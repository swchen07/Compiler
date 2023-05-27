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
 * @brief 声明所有类
 * 
 */

class BaseAST;
class ProgramAST;
class CompUnitAST;
class FuncDef;

class DeclAST;
class VarDeclAST;
class VarDefAST;
class BlockAST;
class StmtAST;
class ReturnStmtAST;
class ExprAST;
class Addition;

class LeftValAST;

class IfElseStmtAST; 
class ForStmtAST; 
class WhileStmtAST;
class BreakStmtAST; 
class ContinueStmtAST; 

class ArgAST; 
class ArgListAST; 
class FuncCallAST; 

class PointerType;
class ArrayType;

using CompUnits = std::vector<CompUnitAST*>;
using Stmts = std::vector<StmtAST*>;
using Exprs = std::vector<ExprAST*>;
using ExprListAST = std::vector<ExprAST*>;

/**
 * @brief type类型的id
 * 
 */

enum TypeID{
    Int, 
    Char, 
	Short,
	Double,
	Ptr,
	Arr
};

class VarType {
public:
	PointerType* _BaseType_pointer;

    VarType(int) {type=Int;}
    VarType(char) {type=Char;}
	VarType(short) {type=Short;}
	// VarType(ArrayType* __BaseType):_BaseType(__BaseType) {type=Arr;}
	VarType(PointerType* __BaseType):_BaseType_pointer(__BaseType) {type=Ptr;}
    VarType(std::string name);
    ~VarType(){}
    TypeID GetType() {return type;}
	llvm::Type* ToLLVMType(IRGenerator&); 
private: 
    TypeID type;
};

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
	ArgListAST* _ArgList;
    BlockAST* block_;

	FuncDefAST(std::string _typeName_, std::string _funcName_, ArgListAST* _ArgList_, BlockAST* _block_ = NULL):
		funcName_(_funcName_), type_(_typeName_), block_(_block_) , _ArgList(_ArgList_){}
	~FuncDefAST(){};
	
    llvm::Value* IRGen(IRGenerator& IRContext);
};

class BlockAST : public BaseAST {
public:
    Stmts* stmts_;
	int varCnt_;

    BlockAST(Stmts* _stmts_): stmts_(_stmts_), varCnt_(0){}
    ~BlockAST(){}

	// void CreatePreDefinedVars(IRGenerator& IRContext); 
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

class VarDeclAST : public DeclAST {
public:
	VarDefAST* varDef_;
    VarType type_; 

	VarDeclAST(std::string _typeName_, VarDefAST* _varDef_) : 
		varDef_(_varDef_), type_(_typeName_) {}
	~VarDeclAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class VarDefAST : public BaseAST {
public:
	std::string varName_; 
    ExprAST* initValue_; 

	VarDefAST(std::string _varName_, ExprAST* _initValue_ = NULL) : 
		varName_(_varName_), initValue_(_initValue_) {}
	~VarDefAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ArrDefAST : public BaseAST {
public:
	llvm::Type* elementType_;
	llvm::Type* arrayType_;
	std::string arrName_;
	VarType type_;
	Exprs* exprs_;


	ArrDefAST(std::string _typeName_, std::string _arrName_, Exprs* _exprs_) :
	type_(_typeName_), arrName_(_arrName_), exprs_(_exprs_) {}
	~ArrDefAST() {}

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
 * @brief branch & control
 * 
 */

class IfElseStmtAST : public StmtAST {
public: 
	ExprAST* cond_; 
	BlockAST* ifBlock_; 
	BlockAST* elseBlock_; 

	IfElseStmtAST(ExprAST* _cond_, BlockAST* _ifBlock_, BlockAST* _elseBlock_):cond_(_cond_), ifBlock_(_ifBlock_), elseBlock_(_elseBlock_){}
	~IfElseStmtAST(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ForStmtAST : public StmtAST {
public: 
	StmtAST* initStmt_; 
	ExprAST* condExpr_; 
	StmtAST* iterStmt_; 
	BlockAST* forBody_; 

	ForStmtAST(StmtAST* _initStmt_, ExprAST* _condExpr_, StmtAST* _iterStmt_, BlockAST* _forBody_):
		initStmt_(_initStmt_), condExpr_(_condExpr_), iterStmt_(_iterStmt_), forBody_(_forBody_){}
	~ForStmtAST(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class WhileStmtAST : public StmtAST {
public: 
	ExprAST* condExpr_; 
	BlockAST* whileBody_; 

	WhileStmtAST(ExprAST* _condExpr_, BlockAST* _whileBody_): 
		condExpr_(_condExpr_), whileBody_(_whileBody_) {}
	~WhileStmtAST(){}; 

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class BreakStmtAST : public StmtAST {
public: 
	BreakStmtAST(){}
	~BreakStmtAST(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
}; 

class ContinueStmtAST : public StmtAST {
public: 
	ContinueStmtAST(){}
	~ContinueStmtAST(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
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

class AssignAST : public StmtAST {
public:
	LeftValAST* LHS_;
	ExprAST* RHS_;

	AssignAST(LeftValAST* _LHS_, ExprAST* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~AssignAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Constant : public ExprAST {
public:
	int int_;
	char character_;
	
	Constant(int _int_) : int_(_int_) {}
	Constant(char _character_) : character_(_character_) {}
	~Constant() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LeftValAST : public  ExprAST {
public:
	std::string name_;

	LeftValAST(std::string& _name_) : name_(_name_) {}
	~LeftValAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
};

//Function argument
class ArgAST : public BaseAST {
public:
	//Its type
	VarType type_;
	//Its name (if any)
	std::string _Name;

	ArgAST(std::string& _typeName_, const std::string& __Name = "") :
		type_(_typeName_), _Name(__Name) {}
	ArgAST(PointerType* _typeName_, const std::string& __Name = "") :
		type_(_typeName_), _Name(__Name) {}
	~ArgAST(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext) { return NULL; }
};

class ArgListAST : public std::vector<ArgAST*>, public BaseAST {
public:
	//Set true if the argument list contains "..."
	bool _VarArgLenth;
	void SetVarArg(void) { this->_VarArgLenth = true; }

	ArgListAST(void) : _VarArgLenth(false) {}
	~ArgListAST(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext) { return NULL; }
};

class FuncCallAST : public ExprAST {
public:
	std::string _FuncName;
	ExprListAST* _ArgList;

	FuncCallAST(const std::string& __FuncName, ExprListAST* __ArgList) : _FuncName(__FuncName), _ArgList(__ArgList) {}
	~FuncCallAST(void) {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class StringType : public Constant {
public:
	std::string _Content;
	StringType(const std::string& __Content) : Constant(0), _Content(__Content) {}
	~StringType(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
};

class AddressOf : public ExprAST {
public:
	LeftValAST* _Operand;
	AddressOf(LeftValAST* __Operand) : _Operand(__Operand) {}
	~AddressOf(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ArrValAST : public ExprAST {
public:
	std::string name_;
	Exprs* exprs_;

	ArrValAST(std::string _name_, Exprs* _exprs_) : name_(_name_), exprs_(_exprs_) {}
	~ArrValAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
};

class AssignArrAST : public StmtAST {
	public:
	ArrValAST* LHS_;
	ExprAST* RHS_;

	AssignArrAST(ArrValAST* _LHS_, ExprAST* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~AssignArrAST() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class PointerType : public BaseAST {
public:
	VarType _BaseType;

	PointerType(std::string __BaseType) : _BaseType(__BaseType) {}
	~PointerType(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext){};
	llvm::Type* ToLLVMType(IRGenerator& IRContext);
};

// class ArrayType : public VarType {
// public:
// 	VarType _BaseType;
// 	size_t _Length;

// 	ArrayType(std::string __BaseType, size_t __Length) : _BaseType(__BaseType), _Length(__Length) {}
// 	ArrayType(std::string __BaseType) : _BaseType(__BaseType), _Length(0) {}
// 	~ArrayType(void) {}
// 	llvm::Type* ToLLVMType(IRGenerator& IRContext);
// };