/**
 * @file AST.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "AST.hpp"
#include <iostream>

llvm::Value* ASSIGNAST::codeGen(CodeGenerator& __Generator) {
    cout << 'ASSIGNAST::codeGen() ' << this->_val << " " << this->_var << endl;
}
