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
};

class CompUnitAST : public BaseAST {
public:

}

class StmtAST : public BaseAST {

}

class ExpAST : public BaseAST {

}

class ReturnAST : public StmtAST {

}

class VarDecl : public StmtAST {

}

class BlockAST : public StmtAST {

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



