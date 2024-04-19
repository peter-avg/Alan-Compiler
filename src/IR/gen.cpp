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
            ret = llvm::ArrayType::get(i8, size);
        }
    }

    if (pass == sym::PassType::reference) {
        ret = ret->getPointerTo();
    }
    return ret;
}

namespace IR {

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
        if (llvm_out) {
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
        } else {
            if (llvm::verifyModule(*module, &llvm::outs())) {
                RaiseLLVMError(BadIRError_c);
            }
            module->print(llvm::outs(), nullptr);
        }
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
        if (pass == sym::PassType::reference) {
            llvm_type = llvm_type->getPointerTo();
        }
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
        IR::BlockPtr newBlock = std::make_shared<IR::FunctionBlock>();
        blocks.push_back(newBlock);
        for (auto par : this->param_list) {
            par->llvm();
        }
        llvm::FunctionType *functype = llvm::FunctionType::get(getLLVMType(this->type, sym::PassType::value), blocks.back()->getParams(), false);
        llvm::Function *func = llvm::Function::Create(functype, llvm::Function::ExternalLinkage, this->id, module.get());
        blocks.back()->setFunction(func);
        scopes.insertFunction(this->id, func);
        scopes.openScope();

        for (auto par : this->param_list) {
            llvm::Argument *arg = func->arg_begin();
            arg->setName(par->getId());
            llvm::Value *alloca = builder.CreateAlloca(arg->getType(), nullptr, par->getId());
            builder.CreateStore(arg, alloca);
            blocks.back()->addValue(par->getId(), alloca, arg->getType(), pass);
        }

        llvm::BasicBlock *FuncBB = llvm::BasicBlock::Create(context, "entry", func);
        builder.SetInsertPoint(FuncBB);
        blocks.back()->setCurrentBlock(FuncBB);
        for (auto decl : def_list) {
            decl->llvm();
        }
        compound->llvm();

        if (func->getReturnType() == proc) {
            builder.CreateRetVoid();
        } else if (func->getReturnType() == i32) {
            builder.CreateRet(c32(0));
        } else if (func->getReturnType() == i8) {
            builder.CreateRet(c8(0));
        }

        blocks.pop_back();
        scopes.closeScope();

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

    // TODO: VarDef by reference for both variables and arrays
    llvm::Value* VarDef::llvm() const {
        // Variable
        if (indeces == INT_MAX) {
            llvm::Value* value = builder.CreateAlloca(getLLVMType(this->type, sym::PassType::value), nullptr, id);
            blocks.back()->addValue(id, value, getLLVMType(this->type, sym::PassType::value), sym::PassType::value);
            return value;
        // Array
        } else { 
            llvm::Value* value = builder.CreateAlloca(getLLVMType(this->type, sym::PassType::reference), nullptr, id);
            blocks.back()->addValue(id, value, getLLVMType(this->type, sym::PassType::reference), sym::PassType::reference);
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
        llvm::Value *exp1 = this->expr1->llvm();
        llvm::Value *exp2 = this->expr2->llvm();
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
        return builder.CreateGlobalStringPtr(this->str);
    }

    // TODO: Add by reference for both variables and arrays
    llvm::Value* LValue::llvm() const {
    if (this->getExpr() == nullptr) {
            return builder.CreateLoad(blocks.back()->getValue(this->id).value);
    }
    else {
        auto *array_index = this->getExpr()->llvm();
            return builder.CreateLoad(builder.CreateGEP(blocks.back()->getValue(this->id).value,std::vector<llvm::Value *>{c32(0), array_index}));
    }
    return nullptr;
    }

    // TODO: This one is a doozy
    llvm::Value* Call::llvm() const {
        llvm::Function *func = scopes.getFunction(id);
        std::vector<llvm::Value*> llvm_args;
        for (auto arg : block) {
            llvm_args.push_back(arg->llvm());
        }
        return builder.CreateCall(func, llvm_args);
    }

    // TODO: Pass by reference for both variables and arrays
    llvm::Value* Assign::llvm() const {
        auto lval = std::static_pointer_cast<ast::LValue>(lvalue);
        auto *exp = this->expr->llvm();
        // Pass by value Variable
        IR::Value val = blocks.back()->getValue(lval->getId());
        if (lval->getExpr() == nullptr) {
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
                return builder.CreateStore(exp, v);
            // Pass by value
            } else {
                std::cout << "Is there an issue here ?" << std::endl;
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

