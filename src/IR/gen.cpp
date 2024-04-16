#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

#include "../ast/ast.hpp"
#include "../symbol/symbol.hpp"
#include "../types/types.hpp"
#include "IR.hpp"

extern char * filename;

static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);
static llvm::Module module(filename, context);

static llvm::Type * i32  = llvm::Type::getInt32Ty(context);
static llvm::Type * i8   = llvm::Type::getInt8Ty(context);
static llvm::Type * proc = llvm::Type::getVoidTy(context);

static llvm::Constant * c32(int n) {
    return llvm::ConstantInt::get(i32, n);
}

static llvm::Constant * c8(unsigned char c) {
    return llvm::ConstantInt::get(i8, c);
}

IR::BlockList blocks;

namespace IR {

    void libgen() {
        
        // writeInteger
        // =============
        llvm::FunctionType *writeIntegerType = llvm::FunctionType::get(proc, i32, false);
        llvm::Function *writeIntegerFunc =
            llvm::Function::Create(writeIntegerType, llvm::Function::ExternalLinkage, "writeInteger", module);

        // writeByte
        // =========
        llvm::FunctionType *writeByteType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeByteFunc =
            llvm::Function::Create(writeByteType, llvm::Function::ExternalLinkage, "writeByte", module);

        // writeChar
        // =========
        llvm::FunctionType *writeCharType = llvm::FunctionType::get(proc, i8, false);
        llvm::Function *writeCharFunc =
            llvm::Function::Create(writeCharType, llvm::Function::ExternalLinkage, "writeChar", module);

        // writeString
        // ===========
        llvm::FunctionType *writeStringType = llvm::FunctionType::get(proc, i8->getPointerTo(), false);
        llvm::Function *writeStringFunc =
            llvm::Function::Create(writeStringType, llvm::Function::ExternalLinkage, "writeString", module);

        // readInteger
        // ===========
        llvm::FunctionType *readIntegerType = llvm::FunctionType::get(i32, {}, false);
        llvm::Function *readIntegerFunc =
            llvm::Function::Create(readIntegerType, llvm::Function::ExternalLinkage, "readInteger", module);

        // readByte
        // ========
        llvm::FunctionType *readByteType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readByteFunc =
            llvm::Function::Create(readByteType, llvm::Function::ExternalLinkage, "readByte", module);

        // readChar
        // ========
        llvm::FunctionType *readCharType = llvm::FunctionType::get(i8, {}, false);
        llvm::Function *readCharFunc =
            llvm::Function::Create(readCharType, llvm::Function::ExternalLinkage, "readChar", module);

        // readString
        // ==========
        llvm::FunctionType *readStringType = llvm::FunctionType::get(proc, {i32, i8->getPointerTo()}, false);
        llvm::Function *readStringFunc =
            llvm::Function::Create(readStringType, llvm::Function::ExternalLinkage, "readString", module);

        // extend
        // ======
        llvm::FunctionType *extendType = llvm::FunctionType::get(i32, i8, false);
        llvm::Function *extendFunc =
            llvm::Function::Create(extendType, llvm::Function::ExternalLinkage, "extend", module);

        // shrink
        // ======
        llvm::FunctionType *shrinkType = llvm::FunctionType::get(i8, i32, false);
        llvm::Function *shrinkFunc =
            llvm::Function::Create(shrinkType, llvm::Function::ExternalLinkage, "shrink", module);

        // strlen
        // ======
        llvm::FunctionType *strlenType = llvm::FunctionType::get(i32, i8->getPointerTo(), false);
        llvm::Function *strlenFunc =
            llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", module);

        // strcmp
        // ======
        llvm::FunctionType *strcmpType = llvm::FunctionType::get(i32, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcmpFunc =
            llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", module);

        // strcpy
        // ======
        llvm::FunctionType *strcpyType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcpyFunc =
            llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", module);

        // strcat
        // ======
        llvm::FunctionType *strcatType = llvm::FunctionType::get(proc, {i8->getPointerTo(), i8->getPointerTo()}, false);
        llvm::Function *strcatFunc =
            llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", module);
    }

    void gen(ast::ASTPtr root) {
        libgen();
        llvm::FunctionType *funcType = llvm::FunctionType::get(proc, false);
        llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
        builder.SetInsertPoint(entry);
        builder.CreateCall(mainFunc, {c32(0)});

        
        root->llvm();
        llvm::verifyFunction(*mainFunc);
        module.print(llvm::outs(), nullptr);
    }

    llvm::Type *translateType(std::string type, sym::PassType pass) {
        llvm::Type *ret = nullptr;
        if (type == "VoidType") ret = llvm::Type::getVoidTy(context);
        if (type == "IntType") ret = llvm::Type::getInt32Ty(context);
        if (type == "ByteType") ret = llvm::Type::getInt8Ty(context);

        if (pass == sym::PassType::reference) {
            return ret->getPointerTo();
        }
        return ret;
    }
}


namespace ast {


    llvm::Value* AST::llvm() const {
        return nullptr;
    }

    llvm::Value* Param::llvm() const {
        // blocks.back()->addParam
        return nullptr;
    }

    llvm::Value* Block::llvm() const {
        for (auto stmt : list ) {
            stmt->llvm();
        }
        return nullptr;
    }

    llvm::Value* Func::llvm() const {
        return nullptr;
    }

    llvm::Value* Const::llvm() const {
        return c32(num);
    }

    llvm::Value* Char::llvm() const {
        return c8(var);
    }

    llvm::Value* VarDef::llvm() const {
        std::string type_name = type->getTypeName();
        llvm::Type *type = IR::translateType(type_name, sym::PassType::value);
        llvm::Value *var = builder.CreateAlloca(type, nullptr, id);

        return var;
    }

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

    llvm::Value* While::llvm() const {
        llvm::Value *n = cond->llvm();
        llvm::BasicBlock *PrevBB = builder.GetInsertBlock();
        llvm::Function *function = PrevBB->getParent();
        llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(context, "loop", function);
        llvm::BasicBlock *BodyBB = llvm::BasicBlock::Create(context, "body", function);
        llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(context, "endwhile", function);
        builder.CreateBr(LoopBB); 
        builder.SetInsertPoint(LoopBB);
        llvm::PHINode *phi_iter = builder.CreatePHI(i32, 2, "iter");
        phi_iter->addIncoming(n, PrevBB);
        llvm::Value *loop_cond = builder.CreateICmpNE(phi_iter, c32(0), "loopcond");
        builder.CreateCondBr(loop_cond, BodyBB, AfterBB);
        builder.SetInsertPoint(BodyBB);
        llvm::Value *remaining = builder.CreateSub(phi_iter, c32(1), "remaining");
        stmt->llvm();
        phi_iter->addIncoming(remaining, builder.GetInsertBlock());
        builder.CreateBr(LoopBB);
        builder.SetInsertPoint(AfterBB);
        return nullptr;
    }

    llvm::Value* If::llvm() const {
        return nullptr;
    }

    llvm::Value* Return::llvm() const {
        return nullptr;
    }

    llvm::Value* BinOp::llvm() const {
        if (expr2 != nullptr) {
            switch(op) {
                case '+': return builder.CreateAdd(expr1->llvm(), expr2->llvm(), "addtmp");
                case '-': return builder.CreateSub(expr1->llvm(), expr2->llvm(), "subtmp");
                case '*': return builder.CreateMul(expr1->llvm(), expr2->llvm(), "multmp");
                case '/': return builder.CreateSDiv(expr1->llvm(), expr2->llvm(), "divtmp");
                case '%': return builder.CreateSRem(expr1->llvm(), expr2->llvm(), "modtmp");
            }
        }
        switch(op) {
            case '+': return builder.CreateAdd(expr1->llvm(), c32(0), "addtmp");
            case '!': return builder.CreateNot(expr1->llvm(), "nottmp");
            case '-': return builder.CreateNeg(expr1->llvm(), "negtmp");
        }
        return c32(0);
    }

    llvm::Value* String::llvm() const {
        return builder.CreateGlobalStringPtr(str);
    }

    llvm::Value* LValue::llvm() const {
        return nullptr;
    }

    llvm::Value* Call::llvm() const {
        return nullptr;
    }

    llvm::Value* Assign::llvm() const {
        return nullptr;
    }

    llvm::Value* Print::llvm() const {
        return nullptr;
    }

}

