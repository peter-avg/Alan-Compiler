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

    std::vector<llvm::Type*> FunctionBlock::getParams() {
        if (params.empty()) {
            return {};
            // RaiseLLVMError(EmptyScopeError_c);
        }

        return params;
    }

    Value FunctionBlock::getValue(std::string name) {
        if (values.find(name) == values.end()) {
            RaiseLLVMError(VariableNotFoundError_c);
        }

        return values[name];
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

    void FunctionBlock::addValue(std::string name, llvm::Value* value, llvm::Type* type, ValueType valueType) {
        values[name] = {value, type, valueType};
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

    void FunctionScope::printFunctions() {
        for (auto funcs : functions) {
            for (auto func : funcs) {
                std::cout << func.first << std::endl;
            }
        }
    }

    llvm::Function *FunctionScope::getFunction(std::string name) {
        std::cout << "Searching for function: " << name << "\n" << std::endl;
        for (auto funcs : functions) {
            for (auto func : funcs) {
                if (func.first == name) {
                    return func.second;
                }
            }
        }

        RaiseLLVMError(FunctionNotFoundError_c);
        return nullptr;
    }
}
