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


#include <llvm/IR/Value.h>
#include <iostream>
#include <vector>

/**
 * @brief 构造所有AST节点的基类，其中用指针管理对象
 * 
 */

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
public:
     std::vector<std::unique_ptr<BaseAST>> Decls_;
    llvm::Value* codeGen(CodeGenContext& context);
    void Dump();
}

/**
 * @brief Decl基类
 * 
 */
class DeclAST : public BaseAST {
public:
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
}

/**
 * @brief Stmt基类和他的子类
 * 
 */
class StmtAST : public BaseAST {
public:
    virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual void Dump() const = 0;
}

class BlockAST : public StmtAST {
public:
    std::unique_ptr<BaseAST> stmts_;

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

/**
 * @brief for(init; loopCond; acc) loopBody
 * 
 */
class ForAST : public StmtAST {
public:
    std::unique_ptr<BaseAST> init_;
    std::unique_ptr<BaseAST> conditon_;
    std::unique_ptr<BaseAST> acc_;
    std::unique_ptr<BaseAST> loopBody_;

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

class IfAST : public StmtAST {
public:
    std::unique_ptr<BaseAST> if_;
    std::unique_ptr<BaseAST> condition_;
    std::unique_ptr<BaseAST> else_;

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

/**
 * @brief while( condition ) whileBody
 * 
 */
class WhileAST : public StmtAST {
    std::unique_ptr<BaseAST> condtion_;
    std::unique_ptr<BaseAST> whileBody_;

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

class ReturnAST : public StmtAST {
public: 
    std::unique_ptr<BaseAST> retVal_;

    ReturnAST(ExpAST* _retVal_) : retVal_(_retVal_) {}
    ~ReturnAST() {}

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

class BreakAST : public StmtAST {
public:

    BreakAST() {}
    ~BreakAST() {}
 
    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

class ContinueAST : public StmtAST {
public:

    ContinueAST() {}
    ~ContinueAST() {}

    llvm::Value* codeGen(CodeGenContext& context) { }
    void Dump();
}

/**
 * @brief Exp基类和他的子类
 * 
 */
class ExpAST : public BaseAST {

}

class BinaryOpAST : public ExpAST {

}

class AssignAST : public ExpAST {

}

class IntAST : public ExpAST {

}

class CharAST : public ExpAST {

}

class IdentifierAST : public ExpAST {

}



