#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <vector>

#include "../ast/ast.hpp"
#include "../symbol/symbol.hpp"
#include "../errors/errors.hpp"
#include "../types/types.hpp"
#include "IR.hpp"

extern char * filename;
extern bool opt;
extern bool llvm_out;

static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);
static std::unique_ptr<llvm::Module> module;
static llvm::legacy::FunctionPassManager *fpm;

static llvm::Type * i32  = llvm::Type::getInt32Ty(context);
static llvm::Type * i8   = llvm::Type::getInt8Ty(context);
static llvm::Type * proc = llvm::Type::getVoidTy(context);
static llvm::Type * i8ptr = llvm::Type::getInt8PtrTy(context);

static llvm::Constant * c32(int n) {
    return llvm::ConstantInt::get(i32, n);
}

static llvm::Constant * c8(unsigned char c) {
    return llvm::ConstantInt::get(i8, c);
}

std::vector<IR::BlockPtr> blocks;
IR::FunctionScope scopes;

llvm::Type *getLLVMType(types::TypePtr type, sym::PassType pass) {
    llvm::Type *ret = nullptr;
    if (type->getTypeName() == "VoidType") ret = proc;
    if (type->getTypeName() == "IntType") ret = i32;
    if (type->getTypeName() == "ByteType") ret = i8;
    if (type->getTypeName() == "IarrayType") {
        int size = type->getSize();
        if (size == 0) {
            ret = i32;
        } else {
            ret = llvm::ArrayType::get(i32, size);
        }
    }

    if (type->getTypeName() == "BarrayType") {
        int size = type->getSize();
        if (size == 0) {
            ret = i8;
        } else {
            // ret = llvm::ArrayType::get(i8, size);
            ret = i8ptr;
        }
    }

    if (pass == sym::PassType::reference) {
        ret = ret->getPointerTo();
    }
    return ret;
}

namespace IR {

    void setupOutput() {
        if (llvm_out) {
            if (llvm::verifyModule(*module, &llvm::outs())) {
                RaiseLLVMError(BadIRError_c);
            }
            module->print(llvm::outs(), nullptr);
        }
        FILE *file = fopen("out.ll", "w");

        if (file == nullptr) {
            RaiseFileError(badfileError_c);
        }

        llvm::raw_fd_ostream os(fileno(file), false); 

        if (llvm::verifyModule(*module, &os)) {
            fclose(file); 
            RaiseLLVMError(BadIRError_c);
        }

        module->print(os, nullptr);
        fclose(file);
    }

    void setupMain(ast::ASTPtr root) {
        auto *mainType = llvm::FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
        auto *mainFunc = llvm::Function::Create(mainType, llvm::Function::ExternalLinkage, "main", module.get());
        llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(context, "entry", mainFunc);
        root->llvm();
        auto alanMain = std::dynamic_pointer_cast<ast::Func>(root);
        auto *alanMainFunc = scopes.getFunction(alanMain->getId());
        std::vector<llvm::Value *> alanArgs;
        builder.SetInsertPoint(mainBB);
        builder.CreateCall(alanMainFunc, alanArgs);
        builder.CreateRet(llvm::ConstantInt::get(i32, 0));
    }
    
    void optimise() {
        if (opt) {
            fpm = new llvm::legacy::FunctionPassManager(module.get());
            fpm->add(llvm::createInstructionCombiningPass());
            fpm->add(llvm::createReassociatePass());
            fpm->add(llvm::createGVNPass());
            fpm->add(llvm::createCFGSimplificationPass());
            fpm->doInitialization();
            for (auto &func : *module) {
                fpm->run(func);
            }
            fpm->doFinalization();
        }
    }

    void libgen() {
        
        // writeInteger
        // =============
        llvm::FunctionType *writeIntegerType = llvm::FunctionType::get(proc, i32, false);
        llvm::Function *writeIntegerFunc =
            llvm::Function::Create(writeIntegerType, llvm::Function::ExternalLinkage, "writeInteger", module.get());

        scopes.insertFunction("writeInteger", writeIntegerFunc);

        // writeByte
        // =========
        llvm::FunctionType *writeByteType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeByteFunc =
            llvm::Function::Create(writeByteType, llvm::Function::ExternalLinkage, "writeByte", module.get());
        
        scopes.insertFunction("writeByte", writeByteFunc);

        // writeChar
        // =========
        llvm::FunctionType *writeCharType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeCharFunc =
            llvm::Function::Create(writeCharType, llvm::Function::ExternalLinkage, "writeChar", module.get());

        scopes.insertFunction("writeChar", writeCharFunc);

        // writeString
        // ===========
        llvm::FunctionType *writeStringType = llvm::FunctionType::get(proc, i8->getPointerTo(), false);
        llvm::Function *writeStringFunc =
            llvm::Function::Create(writeStringType, llvm::Function::ExternalLinkage, "writeString", module.get());

        scopes.insertFunction("writeString", writeStringFunc);

        // readInteger
        // ===========
        llvm::FunctionType *readIntegerType = llvm::FunctionType::get(i32, {}, false);
        llvm::Function *readIntegerFunc =
            llvm::Function::Create(readIntegerType, llvm::Function::ExternalLinkage, "readInteger", module.get());

        scopes.insertFunction("readInteger", readIntegerFunc);

        // readByte
        // ========
        llvm::FunctionType *readByteType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readByteFunc =
            llvm::Function::Create(readByteType, llvm::Function::ExternalLinkage, "readByte", module.get());

        scopes.insertFunction("readByte", readByteFunc);

        // readChar
        // ========
        llvm::FunctionType *readCharType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readCharFunc =
            llvm::Function::Create(readCharType, llvm::Function::ExternalLinkage, "readChar", module.get());

        scopes.insertFunction("readChar", readCharFunc);

        // readString
        // ==========
        llvm::FunctionType *readStringType = llvm::FunctionType::get(proc, {i32, i8->getPointerTo()}, false);
        llvm::Function *readStringFunc =
            llvm::Function::Create(readStringType, llvm::Function::ExternalLinkage, "readString", module.get());

        scopes.insertFunction("readString", readStringFunc);

        // extend
        // ======
        llvm::FunctionType *extendType = llvm::FunctionType::get(i32, i8, false);
        llvm::Function *extendFunc =
            llvm::Function::Create(extendType, llvm::Function::ExternalLinkage, "extend", module.get());

        scopes.insertFunction("extend", extendFunc);

        // shrink
        // ======
        llvm::FunctionType *shrinkType = llvm::FunctionType::get(i8, i32, false);
        llvm::Function *shrinkFunc =
            llvm::Function::Create(shrinkType, llvm::Function::ExternalLinkage, "shrink", module.get());

        scopes.insertFunction("shrink", shrinkFunc);

        // strlen
        // ======
        llvm::FunctionType *strlenType = llvm::FunctionType::get(i32, i8->getPointerTo(), false);
        llvm::Function *strlenFunc =
            llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", module.get());

        scopes.insertFunction("strlen", strlenFunc);

        // strcmp
        // ======
        llvm::FunctionType *strcmpType = llvm::FunctionType::get(i32, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcmpFunc =
            llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", module.get());

        scopes.insertFunction("strcmp", strcmpFunc);

        // strcpy
        // ======
        llvm::FunctionType *strcpyType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcpyFunc =
            llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", module.get());

        scopes.insertFunction("strcpy", strcpyFunc);

        // strcat
        // ======
        llvm::FunctionType *strcatType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcatFunc =
            llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", module.get());

        scopes.insertFunction("strcat", strcatFunc);
    }

    void gen(ast::ASTPtr root) {
        module = std::make_unique<llvm::Module>(filename, context);
        scopes.openScope();
        libgen();
        setupMain(root);
        optimise();
        scopes.closeScope();
        setupOutput();
    }
}


namespace ast {


    // TODO: Done 
    llvm::Value* AST::llvm() const {
        return nullptr;
    }

    // TODO: Should be adding parameters so that the calling function can use them
    llvm::Value* Param::llvm() const {
        llvm::Type *llvm_type = getLLVMType(type, pass);
        blocks.back()->addParam(id, llvm_type, pass);
        blocks.back()->addValue(id, nullptr, getLLVMType(type, pass), pass);
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Block::llvm() const {
        for (auto stmt : list ) {
            stmt->llvm();
        }
        return nullptr;
    }

    // TODO: This one is a doozy
    llvm::Value* Func::llvm() const {
        IR::BlockPtr blockity = std::make_shared<IR::FunctionBlock>();
        blocks.push_back(blockity);
        for (auto par : param_list){
            par->llvm();
        }
        llvm::FunctionType *functype = llvm::FunctionType::get(getLLVMType(type, sym::PassType::value), blocks.back()->getParams(), false);
        llvm::Function *func = llvm::Function::Create(functype, llvm::Function::ExternalLinkage, id, module.get());
        blocks.back()->setFunction(func);
        scopes.insertFunction(id, func);
        scopes.openScope();
        int i = 0;
        for (auto &arg : func->args()) {
            auto param = std::dynamic_pointer_cast<ast::Param>(param_list[i]);
            arg.setName(param->getId());
            i++;
        }
        llvm::BasicBlock *funcBB = llvm::BasicBlock::Create(context, "entry", func);
        builder.SetInsertPoint(funcBB);
        blocks.back()->setCurrentBlock(funcBB);
        for (auto &arg : func->args()) {
            auto *alloca = builder.CreateAlloca(arg.getType(), nullptr, arg.getName());
            if (arg.getType()->isPointerTy()) {
                std::cout << arg.getName().str() << std::endl;
                blocks.back()->addValue(arg.getName().str(), alloca, arg.getType()->getPointerElementType(), sym::PassType::reference);
            }
            else {
                std::cout << arg.getName().str() << std::endl;
                blocks.back()->addValue(arg.getName().str(), alloca, arg.getType(), sym::PassType::value);
            }
            builder.CreateStore(&arg, alloca);
        }
        for (auto def : def_list) {
            def->llvm();
        }
        compound->llvm();
        if (func->getReturnType()->isIntegerTy(32)) {
            builder.CreateRet(c32(0));
        }
        else if (func->getReturnType()->isIntegerTy(8)) {
            builder.CreateRet(c8(0));
        }
        else {
            builder.CreateRetVoid();
        }
        blocks.pop_back();
        scopes.closeScope();

        if (!main) {
            std::cout << "Function " << id << " created" << std::endl;
            builder.SetInsertPoint(blocks.back()->getCurrentBlock());
        }
        
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Const::llvm() const {
        return c32(num);
    }

    // TODO: Done
    llvm::Value* Char::llvm() const {
        return c8(var);
    }

    // TODO: Done
    llvm::Value* VarDef::llvm() const {
        // Variable
        if (indeces == INT_MAX) {
            llvm::Value* value = builder.CreateAlloca(getLLVMType(type, sym::PassType::value), nullptr, id);
            blocks.back()->addValue(id, value, getLLVMType(type, sym::PassType::value), sym::PassType::value);
            // return value;
        // Array
        } else { 
            llvm::Value* value = builder.CreateAlloca(getLLVMType(type, sym::PassType::reference), nullptr, id);
            blocks.back()->addValue(id, value, getLLVMType(type, sym::PassType::reference), sym::PassType::reference);
        }
        return nullptr;
    }

    // TODO: Done
    llvm::Value* Cond::llvm() const {
        if (first == nullptr && second == nullptr) {
            if (operation == "true") {
                return c32(1);
            }
            return c32(0);
        }
        if (operation == "<") return builder.CreateICmpSLT(first->llvm(), second->llvm(), "lttmp");
        if (operation == ">") return builder.CreateICmpSGT(first->llvm(), second->llvm(), "gttmp");
        if (operation == "==") return builder.CreateICmpEQ(first->llvm(), second->llvm(), "eqtmp");
        if (operation == "!=") return builder.CreateICmpNE(first->llvm(), second->llvm(), "netmp");
        if (operation == ">=") return builder.CreateICmpSGE(first->llvm(), second->llvm(), "getmp"); 
        if (operation == "<=") return builder.CreateICmpSLE(first->llvm(), second->llvm(), "letmp");
        if (operation == "&") return builder.CreateAnd(first->llvm(), second->llvm(), "andtmp");
        if (operation == "|") return builder.CreateOr(first->llvm(), second->llvm(), "ortmp");
        return c32(0);
    }

    // TODO: Probably not done, we should be certain about the previous block and the current block
    llvm::Value* While::llvm() const {
        llvm::Function *function = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *CondBB = llvm::BasicBlock::Create(context, "cond", function);
        llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(context, "loop", function);
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(context, "endwhile", function);
        builder.CreateBr(CondBB);
        builder.SetInsertPoint(CondBB);
        llvm::Value *cond = this->cond->llvm();
        builder.CreateCondBr(cond, LoopBB, AfterBB);
        builder.SetInsertPoint(LoopBB);
        stmt->llvm();
        builder.CreateBr(CondBB);
        builder.SetInsertPoint(AfterBB);
        return nullptr;
    }

    // TODO: Probably not done, we should be certain about the previous block and the current block
    llvm::Value* If::llvm() const {
        llvm::Value *n = cond->llvm();
        llvm::BasicBlock *PrevBB = builder.GetInsertBlock();
        llvm::Function *function = PrevBB->getParent();
        llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(context, "then", function);
        llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(context, "else", function);
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(context, "endif", function);
        builder.CreateCondBr(n, ThenBB, ElseBB);
        builder.SetInsertPoint(ThenBB);
        stmt1->llvm();
        builder.CreateBr(AfterBB);
        builder.SetInsertPoint(ElseBB);
        if (stmt2 != nullptr) {
            stmt2->llvm();
        }
        builder.CreateBr(AfterBB);
        builder.SetInsertPoint(AfterBB);
        return nullptr;

    }

    // TODO: Done
    llvm::Value* Return::llvm() const {
        if (expr != nullptr) {
            builder.CreateRet(expr->llvm());
        } else {
            builder.CreateRetVoid();
        }
        return nullptr;
    }

    // TODO: Done
    llvm::Value* BinOp::llvm() const {
        llvm::Value *exp1 = expr1->llvm();
        llvm::Value *exp2 = expr2->llvm();
        if (expr2 != nullptr) {
            switch(op) {
                case '+': return builder.CreateAdd(exp1, exp2, "addtmp");
                case '-': return builder.CreateSub(exp1, exp2, "subtmp");
                case '*': return builder.CreateMul(exp1, exp2, "multmp");
                case '/': return builder.CreateSDiv(exp1, exp2, "divtmp");
                case '%': return builder.CreateSRem(exp1, exp2, "modtmp");
            }
        }
        switch(op) {
            case '+': return builder.CreateAdd(exp1, c32(0), "addtmp");
            case '!': return builder.CreateNot(exp1, "nottmp");
            case '-': return builder.CreateNeg(exp1, "negtmp");
        }
        return c32(0);
    }

    // TODO: Done
    llvm::Value* String::llvm() const {
        return builder.CreateGlobalStringPtr(str);
    }

    // TODO: Done
    llvm::Value* LValue::llvm() const {
        // Variable
        if (expr == nullptr) {
            IR::Value val = blocks.back()->getValue(id);
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value *alloca = builder.CreateLoad(val.value);
                return builder.CreateLoad(alloca);
            // Pass by value
            } else {
                return builder.CreateLoad(val.value);
            }
        }
        // Array
        else {
            llvm::Value * array_index = expr->llvm();
            IR::Value val = blocks.back()->getValue(id);
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value *pointer_to = builder.CreateLoad(val.value);
                llvm::Value *alloca = builder.CreateGEP(pointer_to, array_index);
                return builder.CreateLoad(alloca);
            // Pass by value
            } else {
                llvm::Value *alloca = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                return builder.CreateLoad(alloca);
            }
        }
        return nullptr;
    }

    // TODO: This one is a doozy
    llvm::Value* Call::llvm() const {
        llvm::Function *func = scopes.getFunction(id);
        std::vector<llvm::Value*> llvm_args;
        int i = 0;
        for (auto &arg : func->args()) {
            if (arg.getType()->isPointerTy()) {
                auto variable = std::dynamic_pointer_cast<ast::LValue>(block[i]);
                // It's a variable of sorts 
                if (variable != nullptr) {
                    // It's a variable
                    if (variable->getExpr() == nullptr) {
                        IR::Value val = blocks.back()->getValue(variable->getId());
                        // Pass by reference
                        if (val.valueType == sym::reference) {
                            llvm::Value *alloca = builder.CreateLoad(val.value);
                            llvm_args.push_back(alloca);
                        // Pass by value
                        } else {
                            llvm_args.push_back(val.value);
                        }
                    // It's an array
                    } else {
                        auto array_index = variable->getExpr()->llvm();
                        IR::Value val = blocks.back()->getValue(variable->getId());
                        // Pass by reference
                        if (val.valueType == sym::reference) {
                            llvm::Value *alloca = builder.CreateLoad(val.value);
                            llvm::Value *v = builder.CreateGEP(alloca, array_index);
                            llvm_args.push_back(v);
                        // Pass by value
                        } else {
                            llvm::Value *v = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                            llvm_args.push_back(v);
                        }
                    }
                }
                // It's a string 
                auto string = std::dynamic_pointer_cast<ast::String>(block[i]);
                if (string != nullptr) {
                    llvm_args.push_back(string->llvm());
                }
                i++;
            } else {
                llvm_args.push_back(block[i]->llvm());
                i++;
            }
        }
        return builder.CreateCall(func, llvm_args);
    }

    // TODO: Done
    llvm::Value* Assign::llvm() const {
        auto *exp = expr->llvm();
        auto lval = std::static_pointer_cast<ast::LValue>(lvalue);
        // Pass by value Variable
        IR::Value val = blocks.back()->getValue(lval->getId());
        if (lval->getExpr() == nullptr) {
            auto possible_string = std::dynamic_pointer_cast<ast::String>(expr);
            if (possible_string != nullptr) {
                return builder.CreateStore(exp, val.value);
            }
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value * alloca = builder.CreateLoad(val.value);
                return builder.CreateStore(exp,alloca);
            // Pass by value
            } else {
                return builder.CreateStore(exp,val.value);
            }
        }
        // Pass by value Array
        else {
            auto *array_index = lval->getExpr()->llvm();
            // Pass by reference
            if (val.valueType == sym::reference) {
                llvm::Value * v = builder.CreateLoad(val.value);
                v = builder.CreateGEP(v, array_index);
                return builder.CreateStore(exp, v);
            // Pass by value
            } else {
                llvm::Value * v = builder.CreateGEP(val.value, std::vector<llvm::Value *>{c32(0), array_index});
                return builder.CreateStore(exp, v);
            }
        }
        return nullptr;
    }

    // IGNORE
    llvm::Value* Print::llvm() const {
        return nullptr;
    }

}

