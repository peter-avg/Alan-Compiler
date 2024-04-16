#include "IR.hpp"
#include "../errors/errors.hpp"

namespace IR {

    llvm::BasicBlock* FunctionBlock::getCurrentBlock() {
        return currentBlock;
    }

    void FunctionBlock::setCurrentBlock(llvm::BasicBlock* block) {
        currentBlock = block;
    }

    void FunctionScope::openScope() {
        functions.push_back(functionTable());
    }

    void FunctionScope::closeScope() {
        if (functions.empty()) {
            RaiseLLVMError(EmptyScopeError_c);

        }

        functions.pop_back();
    }

    void FunctionScope::insertFunction(std::string name, llvm::Function* function) {
        functions.back()[name] = function;
    }

    llvm::Function *FunctionScope::getFunction(std::string name) {
        return functions.back()[name];
    }
}
