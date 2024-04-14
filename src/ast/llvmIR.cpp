#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/DerivedTypes.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/IRBuilder.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/LLVMContext.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/Module.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/Type.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/Value.h"
#include "/opt/homebrew/Cellar/llvm@12/12.0.1_1/include/llvm/IR/Verifier.h"

#include "ast.hpp"

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


namespace ast {

    llvm::Value* AST::llvm() const {
        return nullptr;
    }

    llvm::Value* Param::llvm() const {
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
        return nullptr;
    }

    llvm::Value* Char::llvm() const {
        return nullptr;
    }

    llvm::Value* VarDef::llvm() const {
        return nullptr;
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
        auto * function = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *loop = llvm::BasicBlock::Create(context, "loop", function);
        llvm::BasicBlock *after = llvm::BasicBlock::Create(context, "afterloop", function);


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

    void init_llvm(ASTPtr root) {
        // create main function
        llvm::FunctionType *funcType = llvm::FunctionType::get(proc, false);
        llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
        llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
        builder.SetInsertPoint(entry);

        // create printf Function
        llvm::FunctionType *printfType = llvm::FunctionType::get(i32, {llvm::Type::getInt8PtrTy(context)}, true);
        llvm::Function *printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);

        
        root->llvm();
        llvm::verifyFunction(*mainFunc);
        module.print(llvm::errs(), nullptr);
        module.print(llvm::outs(), nullptr);
    }

    void libvm() {
        
        // writeInteger
        // =============
        llvm::FunctionType *writeIntegerType = llvm::FunctionType::get(i32, {i32}, false);
        llvm::Function *writeIntFunc = llvm::Function::Create(writeIntegerType, llvm::Function::ExternalLinkage, "writeInteger", module);

        // writeByte
        // =========
        llvm::FunctionType *writeByteType = llvm::FunctionType::get(i32, {i8}, false);
        llvm::Function *writeByteFunc = llvm::Function::Create(writeByteType, llvm::Function::ExternalLinkage, "writeByte", module);

        // writeChar
        // =========
        llvm::FunctionType *writeCharType = llvm::FunctionType::get(i32, {i8}, false);
        llvm::Function *writeCharFunc = llvm::Function::Create(writeCharType, llvm::Function::ExternalLinkage, "writeChar", module);

        // writeString
        // ===========
        llvm::FunctionType *writeStringType = llvm::FunctionType::get(i32, {llvm::Type::getInt8PtrTy(context)}, false);
        llvm::Function *writeStringFunc = llvm::Function::Create(writeStringType, llvm::Function::ExternalLinkage, "writeString", module);

        // readInteger
        // ===========
        llvm::FunctionType *readIntegerType = llvm::FunctionType::get(i32, false);
        llvm::Function *readIntFunc = llvm::Function::Create(readIntegerType, llvm::Function::ExternalLinkage, "readInteger", module);


        // readByte
        // ========
        llvm::FunctionType *readByteType = llvm::FunctionType::get(i8, false);
        llvm::Function *readByteFunc = llvm::Function::Create(readByteType, llvm::Function::ExternalLinkage, "readByte", module);

        // readChar
        // ========
        llvm::FunctionType *readCharType = llvm::FunctionType::get(i8, false);
        llvm::Function *readCharFunc = llvm::Function::Create(readCharType, llvm::Function::ExternalLinkage, "readChar", module);

        // readString
        // ==========
        llvm::FunctionType *readStringType = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(context), false);
        llvm::Function *readStringFunc = llvm::Function::Create(readStringType, llvm::Function::ExternalLinkage, "readString", module);

        // extend
        // ======
        llvm::FunctionType *extendType = llvm::FunctionType::get(i32, {i8}, false);
        llvm::Function *extendFunc = llvm::Function::Create(extendType, llvm::Function::ExternalLinkage, "extend", module);

        // shrink
        // ======
        llvm::FunctionType *shrinkType = llvm::FunctionType::get(i8, {i32}, false);
        llvm::Function *shrinkFunc = llvm::Function::Create(shrinkType, llvm::Function::ExternalLinkage, "shrink", module);

        // strlen
        // ======
        llvm::FunctionType *strlenType = llvm::FunctionType::get(i32, {llvm::Type::getInt8PtrTy(context)}, false);
        llvm::Function *strlenFunc = llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage, "strlen", module);

        // strcmp
        // ======
        llvm::FunctionType *strcmpType = llvm::FunctionType::get(i32, {llvm::Type::getInt8PtrTy(context), llvm::Type::getInt8PtrTy(context)}, false);
        llvm::Function *strcmpFunc = llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage, "strcmp", module);

        // strcpy
        // ======
        llvm::FunctionType *strcpyType = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(context), {llvm::Type::getInt8PtrTy(context), llvm::Type::getInt8PtrTy(context)}, false);
        llvm::Function *strcpyFunc = llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage, "strcpy", module);

        // strcat
        // ======
        llvm::FunctionType *strcatType = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(context), {llvm::Type::getInt8PtrTy(context), llvm::Type::getInt8PtrTy(context)}, false);
        llvm::Function *strcatFunc = llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", module);

    }

}

