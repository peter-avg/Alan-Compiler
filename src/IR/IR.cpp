#include "IR.hpp"
#include "../errors/errors.hpp"

extern llvm::LLVMContext context;

namespace IR {

    // Getters
    // =======
    llvm::BasicBlock* FunctionBlock::getCurrentBlock() {
        if (currentBlock == nullptr) {
            RaiseLLVMError(EmptyScopeError_c);
        }

        return currentBlock;
    }

    std::vector<llvm::Type*> FunctionBlock::getParams(std::string name) {
        if (params.empty()) {
            RaiseLLVMError(EmptyScopeError_c);
        }

        return params;
    }

    llvm::Type* FunctionBlock::getVar(std::string name) {
        if (vars.find(name) == vars.end()) {
            RaiseLLVMError(VariableNotFoundError_c);
        }

        return vars[name];
    }

    llvm::AllocaInst* FunctionBlock::getValue(std::string name) {
        if (values.find(name) == values.end()) {
            RaiseLLVMError(VariableNotFoundError_c);
        }

        return values[name];
    }

    llvm::AllocaInst* FunctionBlock::getAddress(std::string name) {
        if (addresses.find(name) == addresses.end()) {
            RaiseLLVMError(VariableNotFoundError_c);
        }

        return addresses[name];
    }

    // Setters
    // =======
    void FunctionBlock::setFunction(llvm::Function* function) {
        this->function = function;
    }

    void FunctionBlock::setCurrentBlock(llvm::BasicBlock* block) {
        this->currentBlock = block;
    }

    // Adders
    // ======
    void FunctionBlock::addParam(std::string name, llvm::Type* type, sym::PassType pass) {
        params.push_back(type);
    }

    void FunctionBlock::addVar(std::string name, llvm::Type* type, sym::PassType pass) {
        vars[name] = type;
    }

    void FunctionBlock::addValue(std::string name, llvm::AllocaInst* value) {
        values[name] = value;
    }

    void FunctionBlock::addAddress(std::string name, llvm::AllocaInst* address) {
        addresses[name] = address;
    }

    void FunctionScope::openScope() {
        functions.push_back(std::map<std::string, llvm::Function*>());
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
        for (auto funcs : functions) {
            if (funcs.find(name) != funcs.end()) {
                return funcs[name];
            }
        }

        return nullptr;
    }
}
